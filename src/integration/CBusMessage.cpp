/*****************************************************************************************
 * Copyright (c) 2012 K. Krasheninnikova, M. Krinkin, S. Martynov, A. Smal, A. Velikiy   *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 *****************************************************************************************/

#include "CBusMessage.h"

namespace syropd
{

CBusMessage::CBusMessage(DBusConnection *conn, DBusMessage *msg) : connection(conn), message(msg) { 
}

bool CBusMessage::isDisconnect() {
    // A signal from the bus saying we are about to be disconnected
    if (dbus_message_is_signal(message, "org.freedesktop.Local", "Disconnected"))
        return true;
    else
        return false;
}

bool CBusMessage::isDefConnect() {
    // New network connection is default connection
    if (dbus_message_is_signal(message, "org.freedesktop.NetworkManager.Connection.Active", "PropertiesChanged")) {
        DBusMessageIter iter;
        dbus_message_iter_init(message, &iter);
        return parserStatus(&iter);
    }
    return false;
}

bool CBusMessage::isWiFi() {
    // Construct the message to Active Connection
    DBusMessage *msg;
    msg = dbus_message_new_method_call("org.freedesktop.NetworkManager", // service
            dbus_message_get_path(message), // path
            "org.freedesktop.DBus.Properties", // interface
            "Get"); // method
    
    const char *interfaceDefltActvConctn = "org.freedesktop.NetworkManager.Connection.Active";
    const char *propertyDefltActvConctn = "SpecificObject";
    dbus_message_append_args(msg, DBUS_TYPE_STRING, &interfaceDefltActvConctn, DBUS_TYPE_STRING, &propertyDefltActvConctn, DBUS_TYPE_INVALID);

    // Ask for SpecificObject from ActiveConnection
    DBusMessage *rpl;
    DBusMessageIter iter;
    rpl = dbus_connection_send_with_reply_and_block(connection, msg, -1, NULL);
    dbus_message_iter_init(rpl, &iter);

    // Can we get SSID?
    int type = dbus_message_iter_get_arg_type(&iter);
    if (type == DBUS_TYPE_INVALID) {
        return false;
    }
    if (type == DBUS_TYPE_VARIANT) {
        const char *WPPath;
        DBusMessageIter subiter;
        dbus_message_iter_recurse(&iter, &subiter);
        dbus_message_iter_get_basic(&subiter, &WPPath);
        
        wirelessPropertiesPath = WPPath;
        
        return !wirelessPropertiesPath.empty();
    }
    return false;
    
}

std::string CBusMessage::getSSID() {
    if (wirelessPropertiesPath.empty() && isWiFi())
    {
        // Construct the message to Wireless Properties
        DBusMessage *msg;
        msg = dbus_message_new_method_call("org.freedesktop.NetworkManager", //service
                wirelessPropertiesPath.c_str(), //path
                "org.freedesktop.DBus.Properties", //interface
                "Get"); //method
        const char *interfaceAP = "org.freedesktop.NetworkManager.AccessPoint";
        const char *propertyAP = "Ssid";
        dbus_message_append_args(msg, DBUS_TYPE_STRING, &interfaceAP, DBUS_TYPE_STRING, &propertyAP, DBUS_TYPE_INVALID);

        /* Ask for SSID from Wireless Properties */
        DBusMessage *rpl;
        DBusMessageIter iter;
        rpl = dbus_connection_send_with_reply_and_block(connection, msg, -1, NULL);
        dbus_message_iter_init(rpl, &iter);

        /* Get SSID (finally) */
        parserSSID(&iter);
 
       return SSID;
    } else
        return "null";
}

bool CBusMessage::parserStatus(DBusMessageIter *iter) {
    int type = dbus_message_iter_get_arg_type(iter);
    if (type == DBUS_TYPE_INVALID) {
        return false;
    }
    
    // loop
    if (type == DBUS_TYPE_ARRAY || type == DBUS_TYPE_DICT_ENTRY) {
        DBusMessageIter subiter;
        dbus_message_iter_recurse(iter, &subiter);
        return parserStatus(&subiter);
    }
    
    std::string def = "Default";
    const char *str;
    
    dbus_message_iter_get_basic(iter, &str);
    if (!def.compare(str)) {
        dbus_message_iter_next(iter);
        DBusMessageIter subiter;
        dbus_message_iter_recurse(iter, &subiter);
        dbus_bool_t boolean;
        dbus_message_iter_get_basic(&subiter, &boolean);
        return boolean;
    }
    return false;
}

bool CBusMessage::parserSSID(DBusMessageIter *iter) {
    int type = dbus_message_iter_get_arg_type(iter);
    if (type == DBUS_TYPE_INVALID) {
        return false;
    }
    
    // loop
    if (type == DBUS_TYPE_VARIANT || type == DBUS_TYPE_ARRAY) {
        DBusMessageIter subiter;
        dbus_message_iter_recurse(iter, &subiter);
        return parserSSID(&subiter);
    }

    unsigned char tmp;
    do {
        dbus_message_iter_get_basic(iter, &tmp);
        SSID.push_back(tmp);
    } while (dbus_message_iter_next(iter));
    return true;
}
    
    
    
} // namespace daemon
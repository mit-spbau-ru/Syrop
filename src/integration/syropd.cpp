/*
    sudo apt-get install libglib2.0-dev
    sudo apt-get install libdbus-glib-1-dev
    g++ -o syropd $(pkg-config --cflags glib-2.0 dbus-glib-1) syropd.cpp $(pkg-config --libs glib-2.0 dbus-glib-1)
*/

#include <syslog.h>
#include <string>
#include <string.h>
#include <cstdlib>
#include <glib.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>

static DBusHandlerResult signalFilter(DBusConnection *connection, DBusMessage *message, void *user_data);
bool isNewDefaultConnection(DBusMessageIter *iter);
const char* getWPPath(DBusMessageIter *iter);
bool getSSID(DBusMessageIter *iter, std::string &SSID);

int main(int argc, char **argv) {
    openlog("syropd", LOG_PID, LOG_USER);
    syslog(LOG_NOTICE, "Daemon successfully started\n");
    GMainLoop *loop;
    DBusConnection *bus;
    DBusError error;

    loop = g_main_loop_new(NULL, FALSE);

    dbus_error_init(&error);
    bus = dbus_bus_get(DBUS_BUS_SYSTEM, &error);
    if (!bus) {
        //g_warning("Failed to connect to the D-BUS daemon: %s", error.message);
        syslog(LOG_NOTICE, "Failed to connect to the D-BUS daemon: %s", error.message);
        dbus_error_free(&error);
        exit(EXIT_FAILURE);
    }
    dbus_connection_setup_with_g_main(bus, NULL);

    /* listening to messages from all objects as no path is specified */
    dbus_bus_add_match(bus, "type='signal',sender='org.freedesktop.NetworkManager',interface='org.freedesktop.NetworkManager.Connection.Active'", &error);
    dbus_connection_add_filter(bus, signalFilter, loop, NULL);

    g_main_loop_run(loop);
    syslog(LOG_NOTICE, "bye-bye!\n");
    exit(EXIT_SUCCESS);
}

static DBusHandlerResult signalFilter(DBusConnection *connection, DBusMessage *message, void *user_data) {
    /* User data is the event loop we are running in */
    GMainLoop *loop = reinterpret_cast<GMainLoop*> (user_data);

    /* A signal from the bus saying we are about to be disconnected */
    if (dbus_message_is_signal(message, "org.freedesktop.Local", "Disconnected")) {
        /* Tell the main loop to quit */
        g_main_loop_quit(loop);
        /* We have handled this message, don't pass it on */
        return DBUS_HANDLER_RESULT_HANDLED;
    }/* A signal to the interface */
    else {
        if (dbus_message_is_signal(message, "org.freedesktop.NetworkManager.Connection.Active", "PropertiesChanged")) {
            DBusError error;
            dbus_error_init(&error);

            DBusMessageIter iter;
            dbus_message_iter_init(message, &iter);

            /* Default connection has been changed (?) */
            if (isNewDefaultConnection(&iter)) {

                DBusMessage *msg;
                DBusMessage *rpl;
                int replyTimeout = -1; /*don't timeout*/

                /* Construct the message to Active Connection */
                msg = dbus_message_new_method_call("org.freedesktop.NetworkManager", /*service*/
                        dbus_message_get_path(message), /*path*/
                        "org.freedesktop.DBus.Properties", /*interface*/
                        "Get"); /*method*/
                const char *interfaceDefltActvConctn = "org.freedesktop.NetworkManager.Connection.Active";
                const char *propertyDefltActvConctn = "SpecificObject";
                dbus_message_append_args(msg, DBUS_TYPE_STRING, &interfaceDefltActvConctn, DBUS_TYPE_STRING, &propertyDefltActvConctn, DBUS_TYPE_INVALID);

                /* Ask for SpecificObject from ActiveConnection */
                rpl = dbus_connection_send_with_reply_and_block(connection, msg, replyTimeout, &error);
                dbus_message_iter_init(rpl, &iter);

                /* Can we get SSID? */
                const char* wirelessPropertiesPath = getWPPath(&iter);
                if (wirelessPropertiesPath) {

                    /* Construct the message to Wireless Properties */
                    msg = dbus_message_new_method_call("org.freedesktop.NetworkManager", /*service*/
                            wirelessPropertiesPath, /*path*/
                            "org.freedesktop.DBus.Properties", /*interface*/
                            "Get"); /*method*/
                    const char *interfaceAP = "org.freedesktop.NetworkManager.AccessPoint";
                    const char *propertyAP = "Ssid";
                    dbus_message_append_args(msg, DBUS_TYPE_STRING, &interfaceAP, DBUS_TYPE_STRING, &propertyAP, DBUS_TYPE_INVALID);

                    /* Ask for SSID from Wireless Properties */
                    rpl = dbus_connection_send_with_reply_and_block(connection, msg, replyTimeout, &error);
                    dbus_message_iter_init(rpl, &iter);

                    /* Get SSID (finally) */
                    std::string SSID;
                    if (getSSID(&iter, SSID)) {

                        //TODO: call syrop with SSID
                        g_print("syrop --ssid=%s\n", SSID.c_str());
                        syslog(LOG_NOTICE, "syrop --ssid=%s\n", SSID.c_str());

                    }
                } else {

                    //TODO: call syrop without parameters
                    g_print("syrop\n");
                    syslog(LOG_NOTICE, "syrop\n");

                }
            }

            return DBUS_HANDLER_RESULT_HANDLED;
        }
    }
    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

bool isNewDefaultConnection(DBusMessageIter *iter) {
    int type = dbus_message_iter_get_arg_type(iter);
    if (type == DBUS_TYPE_INVALID) {
        return false;
    }
    if (type == DBUS_TYPE_ARRAY || type == DBUS_TYPE_DICT_ENTRY) {
        DBusMessageIter subiter;
        dbus_message_iter_recurse(iter, &subiter);
        return isNewDefaultConnection(&subiter);
    }

    const char *str;
    dbus_message_iter_get_basic(iter, &str);
    if (!strncmp(str, "Default", 6)) {
        dbus_message_iter_next(iter);
        DBusMessageIter subiter;
        dbus_message_iter_recurse(iter, &subiter);
        dbus_bool_t boolean;
        dbus_message_iter_get_basic(&subiter, &boolean);
        return boolean;
    }
    return false;
}

const char *getWPPath(DBusMessageIter *iter) {
    int type = dbus_message_iter_get_arg_type(iter);
    if (type == DBUS_TYPE_INVALID) {
        return NULL;
    }
    if (type == DBUS_TYPE_VARIANT) {
        const char *wirelessPropertiesPath;
        DBusMessageIter subiter;
        dbus_message_iter_recurse(iter, &subiter);
        dbus_message_iter_get_basic(&subiter, &wirelessPropertiesPath);
        if (strlen(wirelessPropertiesPath) != 1)
            return wirelessPropertiesPath;
    }
    return NULL;
}

bool getSSID(DBusMessageIter *iter, std::string &SSID) {
    int type = dbus_message_iter_get_arg_type(iter);
    if (type == DBUS_TYPE_INVALID) {
        return false;
    }
    if (type == DBUS_TYPE_VARIANT || type == DBUS_TYPE_ARRAY) {
        DBusMessageIter subiter;
        dbus_message_iter_recurse(iter, &subiter);
        return getSSID(&subiter, SSID);
    }

    unsigned char tmp;
    do {
        dbus_message_iter_get_basic(iter, &tmp);
        SSID.push_back(tmp);
    } while (dbus_message_iter_next(iter));
    return true;
}
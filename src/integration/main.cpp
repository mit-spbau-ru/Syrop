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

#include "main.h"

/**
 * This function will be called every time when we caching a message, satisfying our conditions.
 */
static DBusHandlerResult signalEngine(DBusConnection *connection, DBusMessage *message, void *user_data);

int main() {

    openlog("syropd", LOG_PID, LOG_USER);
    DBusError error;
    try {
        GMainLoop *loop = g_main_loop_new(NULL, FALSE);

        DBusConnection *bus;
        dbus_error_init(&error);
        bus = dbus_bus_get(DBUS_BUS_SYSTEM, &error);
        if (!bus) {
            throw daemonexception(error);
        }
        dbus_connection_setup_with_g_main(bus, NULL);

        // listening to messages from all objects as no path is specified
        dbus_bus_add_match(bus, "type='signal',sender='org.freedesktop.NetworkManager',interface='org.freedesktop.NetworkManager.Connection.Active'", &error);
        dbus_connection_add_filter(bus, signalEngine, loop, NULL);

        syslog(LOG_NOTICE, "Daemon successfully started.\n");
        g_main_loop_run(loop);

    } catch (daemonexception& e) {
        std::string message = std::string("Failed to connect to the D-BUS daemon: ") + e.what();
        syslog(LOG_ERR, "%s", message.c_str());
        dbus_error_free(&error);
        exit(EXIT_FAILURE);
    } catch (const std::exception& e) {
        std::string message = std::string("Error: ") + e.what();
        syslog(LOG_ERR, "%s", message.c_str());
        exit(EXIT_FAILURE);
    }


    exit(EXIT_SUCCESS);
}

static DBusHandlerResult signalEngine(DBusConnection *connection, DBusMessage *message, void *user_data) {

    CBusMessage msg(connection, message);

    if (msg.isDisconnect()) {
        CExecuter execute(false);
        syslog(LOG_NOTICE, "rollback\n");
    } else {
        if (msg.isDefConnect()) {
            std::string log = "New connection detected";
            if (msg.isWiFi()) {

                errno = 0;
                std::ifstream in(mapping_file().c_str());

                if (in.fail())
                    throw std::runtime_error(error_message(errno));

                networks_t data;
                in >> data;
                in.close();

                std::string SSID = msg.getSSID();
                CFinder predicate(SSID);
                // Profile search by network name
                const networks_t::const_iterator it = find(data, predicate);

                if (it != data.end()) {
                    CExecuter execute(it->first);
                    log += ". Syrop is configurated for network " + SSID + "(" + it->first + ")";
                } else {
                    log += ", but there is no record about it in a database.\n";
                }

            } else {
                log += ", but is is not Wifi connection.\n";
            }
            syslog(LOG_NOTICE, "%s", log.c_str());
        }
    }

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}
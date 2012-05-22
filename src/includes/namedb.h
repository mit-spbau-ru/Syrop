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

#ifndef _INCLUDES_NAMES_DB_H_
#define _INCLUDES_NAMES_DB_H_

#include <string>
#include <vector>

#include "inidata.h"

namespace utils {

    struct NetworkAttributes {
        /* empty string is meanning that attribute value is unknown */
        std::string config;     //ini file section name = network config
        std::string essid;      //wireless network essid
        std::string gwip;       //default gateway ip
        std::string netmask;    //subnetwork mask
        std::string dev;        //network device
        std::string profile;    //network profile
    };

    typedef std::vector<NetworkAttributes> networks_t;

    class NamesDataBase {
    public:
        /**
         * Opens ini file, and reads network attributes
         *
         * @param file file name
         */
        NamesDataBase(std::string const &file);
        
        void reload();

        /**
         * Creates an empty database of network parameters
         */
        //NamesDataBase() {
        //}

        /**
         * Add network description to a database
         *
         * @param attrs network description
         */
        //void addDescription(NetworkAttributes const &attrs) {
        //    myBase.push_back(attrs);
        //}

        /**
         * Flush database to file
         *
         * @param file file name
         */
        //void write(std::string const &file);

        /**
         * Adds all known NetworkAttributes that satisfies checker test
         *
         * @param checker any entity that allow to write checker(attr) and return bool, where attr is
         * NetworkAttributes const&
         * @param result vector of NetworkAttributes where filtered attributes will be placed
         */
        template <class QueryChecker>
        void filter(QueryChecker const &checker, networks_t &result) const {
            for (networks_t::const_iterator it = myBase.begin(); it != myBase.end(); ++it) {
                if (checker(*it))
                    result.push_back(*it);
            }
        }
        
        std::string getProfileBySsid(std::string const &SSID, networks_t &result) const {
            for (networks_t::const_iterator it = myBase.begin(); it != myBase.end(); ++it) {
                if (it->essid == SSID)
                    return it->profile;
            }
            return (std::string)"default";
        }

    private:
        networks_t myBase;
        std::string const filename;

        void readNetworkAttributes(IniData const &data, std::string const &network);
    };

} // namespace utils

#endif // _INCLUDES_NAMES_DB_H_
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

#include "CExecuter.h"

namespace syropd
{

CExecuter::CExecuter(bool) {
    char* const argv[] = {(char *) "syrop", (char *) "-r", (char *) 0};
}

CExecuter::CExecuter(std::string profile) {
    char* const argv[] = {(char *) "syrop", (char *) "-a", const_cast<char*> (profile.c_str()), (char *) 0};
}

void CExecuter::exec(char* const argv[]) {
    pid_t pID = fork();

    if (pID == 0) {
                
        if (execv("/usr/bin/syrop", argv))
        {
            std::cerr << "An unknown error has occurred with SSID " << argv[1] << std::endl;
            exit(EXIT_FAILURE);
        }
        result = 0;

        exit(EXIT_SUCCESS);
    } else if (pID < 0) {
        std::cerr << "Failed to fork" << std::endl;
        result = 1;
    }
}

} // namespace daemon
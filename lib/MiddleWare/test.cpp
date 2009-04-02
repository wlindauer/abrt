/*
    test.cpp - simple library test

    Copyright (C) 2009  Zdenek Prikryl (zprikryl@redhat.com)
    Copyright (C) 2009  RedHat inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    */

#include "MiddleWare.h"
#include "DebugDump.h"
#include "CrashTypes.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>


int main(int argc, char** argv)
{

    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <DebugDumpDir>" << std::endl;
    }
    try
    {
        //std::string(CONF_DIR) + "/abrt.conf"
        CMiddleWare middleWare(PLUGINS_CONF_DIR,
                               PLUGINS_LIB_DIR);
        /* Create DebugDump */
        /* Try to save it into DB */
        middleWare.RegisterPlugin("CCpp");
        middleWare.RegisterPlugin("Logger");
        middleWare.RegisterPlugin("RunApp");
        middleWare.RegisterPlugin("SQLite3");
        middleWare.SetDatabase("SQLite3");
        middleWare.SetOpenGPGCheck(false);
        middleWare.AddAnalyzerReporter("CCpp", "Logger");
        middleWare.AddAnalyzerAction("CCpp", "RunApp", "date,action_date");
        std::cout << "sasas" <<std::endl;
        map_crash_info_t crashInfo;
        if (middleWare.SaveDebugDump(argv[1], crashInfo))
        {
            std::cout << "Application Crashed! " <<
                         crashInfo[item_crash_into_t_str[CI_PACKAGE]][CD_CONTENT] << ", " <<
                         crashInfo[item_crash_into_t_str[CI_EXECUTABLE]][CD_CONTENT] << ", " <<
                         crashInfo[item_crash_into_t_str[CI_COUNT]][CD_CONTENT] << ", " << std::endl;

            /* Get Report, so user can change data (remove private stuff)
             * If we do not want user interaction, just send data immediately
             */
            map_crash_report_t crashReport;
            middleWare.CreateCrashReport(crashInfo[item_crash_into_t_str[CI_UUID]][CD_CONTENT],
                                         crashInfo[item_crash_into_t_str[CI_UID]][CD_CONTENT],
                                         crashReport);
            /* Report crash */
            middleWare.Report(crashReport);
        }
    }
    catch (std::string sError)
    {
        std::cerr << sError << std::endl;
    }

    return 0;
}

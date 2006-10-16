// 
//   Copyright (C) 2005, 2006 Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

// Linking Gnash statically or dynamically with other modules is making a
// combined work based on Gnash. Thus, the terms and conditions of the GNU
// General Public License cover the whole combination.
//
// As a special exception, the copyright holders of Gnash give you
// permission to combine Gnash with free software programs or libraries
// that are released under the GNU LGPL and with code included in any
// release of Talkback distributed by the Mozilla Foundation. You may
// copy and distribute such a system following the terms of the GNU GPL
// for all but the LGPL-covered parts and Talkback, and following the
// LGPL for the LGPL-covered parts.
//
// Note that people who make modified versions of Gnash are not obligated
// to grant this special exception for their modified versions; it is their
// choice whether to do so. The GNU General Public License gives permission
// to release a modified version without this exception; this exception
// also makes it possible to release a modified version which carries
// forward this exception.
// 
//

// This is generated by autoconf
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <sys/types.h>
#include <sys/stat.h>

#include "tu_types.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "log.h"
#include "rc.h"

using namespace std;
namespace gnash {

RcInitFile rcfile;


RcInitFile::RcInitFile() : _delay(0),
                           _debug(false),
                           _debugger(false),
                           _verbosity(-1),
                           _actiondump(false),
                           _parserdump(false),
                           _splash_screen(true),
                           _localdomain_only(false),
                           _localhost_only(false),
                           _sound(true),
                           _plugin_sound(false)
{
//    GNASH_REPORT_FUNCTION;
//    loadFiles();
}

RcInitFile::~RcInitFile()
{
//    GNASH_REPORT_FUNCTION;    
}

// Look for a config file in the likely places.
bool
RcInitFile::loadFiles()
{
//    GNASH_REPORT_FUNCTION;
    
    // Check the default system location
    string loadfile = "/etc/gnashrc";
    parseFile(loadfile);
    
    // Check the default config location
    loadfile = "/usr/local/etc/gnashrc";
    parseFile(loadfile);
    
    // Check the users home directory
    char *home = getenv("HOME");
    if (home) {
        loadfile = home;
        loadfile += "/.gnashrc";
        return parseFile(loadfile);
    }
    
    return false;
}

bool
RcInitFile::extractSetting(bool *var, const char *pattern, std::string &variable,
                           std::string &value)
{
//    GNASH_REPORT_FUNCTION;
//    dbglogfile << variable << ": " << value << endl;
    
    if (variable == pattern) {
        if ((value == "on") || (value == "yes") || (value == "true")) {
//            dbglogfile << variable << ": Enabled " << endl;
            *var = true;
        }
        if ((value == "off") || (value == "no") || (value == "false")) {
//            dbglogfile << variable << ": Disabled " << endl;
            *var = false;
        }
    }
    return *var;
}

int
RcInitFile::extractNumber(int *num, const char *pattern, std::string &variable,
                           std::string &value)
{      
//    GNASH_REPORT_FUNCTION;
//        dbglogfile << variable.c_str() << ": " << value.c_str() << endl;
    if (variable == pattern) {
        *num = strtol(value.c_str(), NULL, 0);
    }
    return *num;
}

// Parse the config file and set the variables.
bool
RcInitFile::parseFile(string filespec)
{
//    GNASH_REPORT_FUNCTION;
    struct stat stats;
    string action;
    string variable;
    string value;
    ifstream in;
    
//  dbglogfile << "Seeing if " << filespec << " exists." << endl;
    if (filespec.size() == 0) {
        return false;
    }
    
    if (stat(filespec.c_str(), &stats) == 0) {
        in.open(filespec.c_str());
        
        if (!in) {
            dbglogfile << "ERROR: Couldn't open file: " << filespec << endl;
            return false;
        }
        
        // Read in each line and parse it
        while (!in.eof()) {
            // Get the first token
            in >> action;
            // Ignore comment lines
            if (action[0] == '#') {
//        dbglogfile << "Ignoring comment line " << endl;
                // suck up the rest of the line
                char name[128];
                in.getline(name, 128);
                continue;
            }
            
            in >> variable >> value;
            //      dbglogfile << action << variable << value << endl;
            
            if (action == "set") {
                extractSetting(&_splash_screen, "splash_screen", variable, value);
                extractSetting(&_localhost_only, "localhost", variable, value);
                extractSetting(&_localdomain_only, "localdomain", variable, value);
                extractSetting(&_debugger, "debugger", variable, value);
                extractSetting(&_actiondump, "actionDump", variable, value);
                extractSetting(&_parserdump, "parserDump", variable, value);
                extractSetting(&_writelog, "writelog", variable, value);
                extractSetting(&_sound, "sound", variable, value);
                extractSetting(&_plugin_sound, "pluginsound", variable, value);
                
                extractNumber(&_delay, "delay", variable, value);
                extractNumber(&_verbosity, "verbosity", variable, value);
                
                if (variable == "documentroot") {
                    _wwwroot = value;
                }
                
                if (variable == "blacklist") {
                    string::size_type pos;
                    while ((pos = value.find(':', 0)) != string::npos) {
                        _blacklist.push_back(value.substr(0, pos));
                        value.erase(0, pos+1);
                    }
                    _blacklist.push_back(value);
                    continue;
                }
                if (variable == "whitelist") {
                    string::size_type pos;
                    while ((pos = value.find(':', 0)) != string::npos) {
                        _whitelist.push_back(value.substr(0, pos));
                        value.erase(0, pos+1);
                    }
                    _whitelist.push_back(value);
                    continue;
                }
            }
        }
    } else {
        if (in) {
            in.close();
        }
        return false;
    }  
    
    if (in) {
        in.close();
    }
    
    
    return true;
}

// Write the changed settings to the config file
bool
RcInitFile::updateFile(string /* filespec */)
{
    cerr << __PRETTY_FUNCTION__ << "ERROR: unimplemented!" << endl;
    return false;
}

void
RcInitFile::useSplashScreen(bool value)
{
    _splash_screen = value;
}

void
RcInitFile::useLocalDomain(bool value)
{
    _localdomain_only = value;
}

void
RcInitFile::useLocalHost(bool value)
{
    _localhost_only = value;
}

void
RcInitFile::useActionDump(bool value)
{
//    GNASH_REPORT_FUNCTION;
    _actiondump = value;
    if (value) {
        _verbosity++;
    }
}

void
RcInitFile::useParserDump(bool value)
{
//    GNASH_REPORT_FUNCTION;
    
    _parserdump = value;
    if (value) {
        _verbosity++;
    }
}

void
RcInitFile::useWriteLog(bool value)
{
//    GNASH_REPORT_FUNCTION;
    
    _writelog = value;
}

void
RcInitFile::dump()
{
    cerr << endl << "Dump RcInitFile:" << endl;
    cerr << "\tTimer interupt delay value: " << _delay << endl;
    cerr << "\tFlash debugger: "
         << ((_debugger)?"enabled":"disabled") << endl;
    cerr << "\tVerbosity Level: " << _verbosity << endl;
    cerr << "\tDump ActionScript processing: "
         << ((_actiondump)?"enabled":"disabled") << endl;
    cerr << "\tDump parser info: "
         << ((_parserdump)?"enabled":"disabled") << endl;
    cerr << "\tUse Splash Screen: "
         << ((_splash_screen)?"enabled":"disabled") << endl;
    cerr << "\tUse Local Domain Only: "
         << ((_localdomain_only)?"enabled":"disabled") << endl;
    cerr << "\tUse Localhost Only: "
         << ((_localhost_only)?"enabled":"disabled") << endl;
    cerr << "\tWrite Debug Log To Disk: "
         << ((_writelog)?"enabled":"disabled") << endl;
    cerr << "\tEnable sound: "
         << ((_sound)?"enabled":"disabled") << endl;
    cerr << "\tEnable Pl,ugin sound: "
         << ((_plugin_sound)?"enabled":"disabled") << endl;
    if (_log.size()) {
        cerr << "\tDebug Log name is: " << _log << endl;
    }
    
//     std::vector<std::string> _whitelist;
//     std::vector<std::string> _blacklist;
}


} // end of namespace gnash

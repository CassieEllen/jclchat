// chatmain.cpp
//
// <one line to give the program's name and a brief idea of what it does.>
// Copyright (C) <year>  <name of author>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier:	GPL-3.0

#include <iostream>

#include <JclServer/JclServerApp.hpp>

using namespace std;
using namespace jcl;


ostream& copyrightNotice(ostream& os)
{
    const char * s = R"str(
    <program>  Copyright (C) <year>  <name of author>
    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
    This is free software, and you are welcome to redistribute it
    under certain conditions; type `show c' for detail
    )str";
    os << s << endl;
}

ostream& notes(ostream& os)
{
   const char * s = R"str(
On Unix platforms, an application built on top of the ServerApplication class can be optionally run as a daemon by giving the —daemon command line option. A daemon, when launched, immediately forks off a background process that does the actual work. After launching the background process, the foreground process exits. 

When running as a daemon, specifying the —pidfile option (e.g., —pidfile=/var/run/sample.pid) may be useful to record the process ID of the daemon in a file. The PID file will be removed when the daemon process terminates (but not, if it crashes). 
)str";
   os << s << endl;
}

int main(int argc, char **argv)
{
  cout << "jcbchat server" << endl;
  cout << copyrightNotice << endl;
  cout << notes << endl;

  JclServerApp app;
  return app.run(argc, argv);

}

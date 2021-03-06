// File.cpp
//
// <one line to give the program's name and a brief idea of what it does.>
// Copyright (C) 2018 Cassie E Nicol
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

#include <Util/File.hpp>

namespace jcl {
    using namespace std;

#if 0
  File::_mimeMap =
    {
      {"css", "text/css"},
      {"ico", "image/x-icon"},
      {"js",  "text/javascript"}
    };
#endif

  bool File::hasMimeType(const string& extension)
    {
        File::_mimeMap.end()  !=  File::_mimeMap.find(extension);
    }

    string File::getMimeType(const string& extension)
    {
      return string();
    }

    bool File::exists(const string& path)
    {
        return false;
    }
}
    

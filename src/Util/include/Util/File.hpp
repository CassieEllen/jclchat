// File.hpp
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

#ifndef File_INCLUDED
#define File_INCLUDED

#include <map>
#include <string>

namespace jcl {

    class File {
    public:
        /// @brief Get the file's mime type
        /// @param extension file extensions
        /// @return true if the extension is a mime type.
        static bool hasMimeType(const std::string &extension);

        /// @brief Get the file's mime type
        /// @param extension file extensions
        /// @return !empty() if the mime type was found
        static std::string getMimeType(const std::string &extension);

        /// @brief Check that the file exists
        /// @param path The full path to the file
        /// @return true if the file was found
        static bool exists(const std::string &path);

        /// @brief
        static std::map<std::string, std::string> _mimeMap;

    };

}
#endif // File_INCLUDED

// HtmlTags.cpp
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

#include <Util/HtmlTags.hpp>

#include <sstream>

namespace jcl {
    using namespace std;
    using namespace Poco::Net;

    string HtmlTags::tableEntry(const string &key, const string &value) {
        ostringstream os;

        os << "<tr><th>" << key << "</th><td>" << value << "</td></tr>";
        os << endl;
        return os.str();
    }

    string HtmlTags::tableEntry(pair<string, string> value) {
        ostringstream os;

        os << "<tr><th>" << value.first << "</th><td>" << value.second << "</td></tr>";
        return os.str();
    }

    string HtmlTags::input(NameValueCollection &values) {
        ostringstream os;
        string type = values.get("type");
        os << "<input type=\"" << type << "\"";

        os << ">\n";
        return os.str();
    }
}
    

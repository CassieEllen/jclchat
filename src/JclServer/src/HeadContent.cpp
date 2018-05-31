/// @brief HeadContent.cpp
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

#include <JclServer/HeadContent.hpp>

#include <JclServer/Page.hpp>

#include <iostream>

namespace jcl {
    using namespace std;

    HeadContent::HeadContent(Page& page)
            : PageContent("head", page)
    {
    }
    
    std::ostream& HeadContent::write(std::ostream& os) const {
        string title = _page.getFormData().get("page.title", "page.title");

        os << "<head>" << endl
            << "<title>" << title << "</title>" << endl;

        os <<  "<script type='text/javascript' src='" << "/scripts/jquery.js'></script>" << endl;
        //os <<  "<link type='text/css' href='/css/jclchat.css' rel='stylesheet' />" << endl;
        os << "</head>" << endl;
    }

}
    
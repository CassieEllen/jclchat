// HeaderContent.cpp
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

#include <JclServer/HeaderContent.hpp>

#include <JclServer/Page.hpp>

#include <Poco/Exception.h>

#include <iostream>


namespace jcl {
    using namespace std;
    using Poco::Exception;

    HeaderContent::~HeaderContent()
    {
    }
    
    ostream& HeaderContent::write(ostream& os) const
    {
        auto data = _page.getFormData();
        //auto h1 = data.get("page.h1", "page.h1");
        string h1 {"oops"};
        try {
            h1 = data.get("page.h1");
        } catch(Exception& e) {
            cerr << "Exception: " << e.message() << endl;
        }
        os << "<!-- " << __PRETTY_FUNCTION__ << " -->" << endl;
        os << "<h1>" << h1 << "</h1>" << endl
           << R"msg(<a href="\">Home</a>)msg"
           << "<hr>" << endl;
    }
    
}
    

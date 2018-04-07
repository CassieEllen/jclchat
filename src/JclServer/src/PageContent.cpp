// PageContent.cpp
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

#include <JclServer/PageContent.hpp>

#include <iostream>


namespace jcl {
    using namespace std;

    PageContent::PageContent(const std::string& name, Page& page)
        : _name(name)
        , _page(page)
    {
    }

    const std::string& PageContent::name() const
    {
        return _name;
    }

    
    void PageContent::setName(const std::string& name)
    {
        _name = name;
    }

    ostream& PageContent::write(ostream& os) const
    {
        os << "PageContent" << endl;
        return os;
    }

}
    

// TextContent.cpp
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

#include <JclServer/TextContent.hpp>

#include <ostream>

namespace jcl {
    using namespace std;

    TextContent::TextContent(const std::string &name, Page& page)
        : PageContent(name, page)
    {
    }

    TextContent::TextContent(const std::string &name, const std::string &text, Page &page)
        :   PageContent(name, page)
        , _text(text)
    {

    }

    TextContent::~TextContent()
    {
    }
    
    void TextContent::setText(const string& text)
    {
        _text = text;
    }
    
    ostream& TextContent::write(ostream& os) const
    {
        os << _text << endl;
        return os;
    }

}
    

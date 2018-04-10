// PageContent.hpp
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

#ifndef PageContent_INCLUDED
#define PageContent_INCLUDED

#include <JclServer/Types.hpp>
#include <JclServer/PocoClasses.hpp>

#include <Poco/Net/NameValueCollection.h>

#include <string>
#include <vector>

namespace jcl {

    class Page;

    class PageContent
    {
    public:
        
        PageContent() = delete;
        PageContent(const std::string& name, Page& page);
        virtual ~PageContent() = default;

        const std::string& name() const;
        void setName(const std::string& name);
    
        virtual std::ostream& write(std::ostream& os) const;

    protected:
        std::string _name;
        Page& _page;
    };

    inline std::ostream& operator<<(std::ostream& os, const PageContent& rhs)
    {
        return rhs.write(os);
    }

}
#endif // PageContent_INCLUDED

// Page.hpp
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

#ifndef Page_INCLUDED
#define Page_INCLUDED

#include <JclServer/PocoClasses.hpp>
#include <JclServer/Types.hpp>

#include <memory>
#include <string>
#include <vector>


namespace jcl {

    class PageContent;
    
class Page
{
public:
    typedef std::vector< std::shared_ptr<PageContent> > content_ptr;
    
public:
    Page(const std::string& name, FormData* pData = nullptr);
    void send(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

    void add(PageContent* content);
    void addAfter(const std::string& name, PageContent* content);

    const std::string& getName() const
    {
        return _name;
    }

    FormData* getFormData() const
    {
        return _formData;
    }

private:
    std::string _name;
    FormData* _formData;
    std::vector< std::shared_ptr<PageContent> > _content;
};

}
#endif // Page_INCLUDED

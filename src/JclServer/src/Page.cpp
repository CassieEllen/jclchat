// Page.cpp
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

#include <JclServer/Page.hpp>
#include <JclServer/PageContent.hpp>
#include <JclServer/HeadContent.hpp>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Exception.h>

#include <iostream>


namespace jcl {
    using namespace std;
    using namespace Poco::Net;
    
    using Poco::Net::HTTPServerRequest;
    using Poco::Net::HTTPServerResponse;
    using Poco::NullPointerException;
    using Poco::Net::NameValueCollection;
    
    Page::Page(const std::string& name, Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
        : _name(name)
        , _request(request)
        , _response(response)
    {
        cout << __PRETTY_FUNCTION__ << endl;

        // Set the default page title.
        if( ! _formData.has("page.title") ) {
            _formData.set("page.title", "jclchat");
        }
    }

    Page::~Page()
    {

    }

    void Page::send()
    {
        //_logger.trace(__PRETTY_FUNCTION__);

        HeadContent headContent(*this);
        _response.setStatus(HTTPResponse::HTTP_OK);
        _response.setContentType("text/html");

        ostream& out = _response.send();

        out << "<html>" << endl;
        out << headContent;
        out << "<body>" << endl;

        for(auto content: _content) {
            //out << *content;
            content->write(out);
        }
        out << "</body>" << "</html>" << endl;
    }

    void Page::add(PageContent* content)
    {
        shared_ptr<PageContent> p(content);
        _content.push_back( p );
    }

    // Has a odd side-effect of inserting at the end if the named element is not found. 
    void Page::addAfter(const string& name, PageContent* content)
    {
        auto it
            = find_if(_content.begin(), _content.end(),
                      [&name](shared_ptr<PageContent> e)->bool{ return e->name() == name; } );

        shared_ptr<PageContent> p(content);

        if(it == _content.end()) {
            _content.push_back( p );
        } else {
            ++it;
            _content.insert(it, p);
        }
    }

}

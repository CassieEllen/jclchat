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
#include <JclServer/HeaderContent.hpp>
#include <JclServer/FooterContent.hpp>
#include <JclServer/TextContent.hpp>

#include <Poco/Util/Application.h>
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

    Page::Page(const std::string &name, Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
            : _name(name), _request(request), _response(response), _formData(), _content(),
              _logger(Poco::Logger::get("Page"))
    {
        string level = Poco::Util::Application::instance().config().getString("application.log_level", "none");
        _logger.setLevel(level);

        _logger.trace(__PRETTY_FUNCTION__);

        // Set the default getPage title.
        if (!_formData.has("getPage.title")) {
            _formData.set("getPage.title", "jclchat");
        }

        // Add in the head section
        add(make_shared<TextContent>("doctype", "<!DOCTYPE html>"));
        add(make_shared<TextContent>("html", "<html>"));
        add(make_shared<HeadContent>());
        add(make_shared<TextContent>("body", "<body>"));
        add(make_shared<HeaderContent>());
    }

    Page::~Page() {
        _logger.trace(__PRETTY_FUNCTION__);

    }

    void Page::send() {
        _logger.trace(__PRETTY_FUNCTION__ + _name);

        // Show contents of _formData
        _logger.debug("_formData contents");
        for (auto it : _formData) {
            _logger.debug("\t" + it.first + ": " + it.second);
        }

        // Give and OK response, and set the getPage content to HTML
        _response.setStatus(HTTPResponse::HTTP_OK);
        _response.setContentType("text/html");

        ostream &out = _response.send();

        add(make_shared<FooterContent>());
        add(make_shared<TextContent>("/body", "</body>"));
        add(make_shared<TextContent>("/html", "</html>"));

        for (auto content: _content) {
            content->write(out);
        }
    }

    void Page::add(const std::shared_ptr<PageContent> &content) {
        _logger.trace(__PRETTY_FUNCTION__ + content->getName());

        content->setPage(this);

        _content.push_back(content);
    }

    // Has a odd side-effect of inserting at the end if the named element is not found. 
    void Page::addAfter(const string &name, std::shared_ptr<PageContent> &content) {
        _logger.trace(__PRETTY_FUNCTION__ + content->getName());

        shared_ptr<PageContent> p(content);

        p->setPage( this );


        auto it
                = find_if(_content.begin(), _content.end(),
                          [&name](shared_ptr<PageContent> e) -> bool { return e->getName() == name; });

        if (it == _content.end()) {
            _content.push_back(p);
        } else {
            ++it;
            _content.insert(it, p);
        }
    }

}

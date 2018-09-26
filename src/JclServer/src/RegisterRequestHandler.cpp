// RegisterHandler.cpp
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

#include <JclServer/RegisterRequestHandler.hpp>

#include <JclServer/Page.hpp>
#include <JclServer/RegisterContent.hpp>
#include <JclServer/TextContent.hpp>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/OptionException.h>
#include <Poco/Net/HTMLForm.h>

#include <iostream>

namespace jcl {
    using namespace std;
    using namespace Poco::Net;

    //------------------------------------------------------------------------

    RegisterRequestHandler::RegisterRequestHandler()
        : _logger(Poco::Logger::get("RegisterRequestHandler"))
    {
        _logger.setLevel(Poco::Message::PRIO_TRACE);
        //_logger.trace(__PRETTY_FUNCTION__);
    }

    RegisterRequestHandler::~RegisterRequestHandler()
    {

    }

    void RegisterRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) {
        NameValueCollection messages;

        HTMLForm form(request, request.stream() );
        for(auto it : form) {
            cout << it.first << ": " << "\"" << it.second << "\"" << endl;
        }
        request.set("register.error", "oops");
        write(request, response);
    }

    void RegisterRequestHandler::write(HTTPServerRequest &request, HTTPServerResponse &response) {
        _logger.trace(__PRETTY_FUNCTION__);

        Page page("Register", request, response);
        auto &data = page.getFormData();
        data.set("getPage.title", "Register");
        data.set("getPage.h1", "Register");

        page.add(make_shared<RegisterContent>());

        page.send();
    }

}

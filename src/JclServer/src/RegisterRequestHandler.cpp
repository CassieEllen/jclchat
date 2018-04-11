// RegisterRequestHandler.cpp
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

namespace jcl {
    using namespace std;

    RequestRequestHandler::RequestRequestHandler()
            : _logger(Poco::Logger::get("RequestRequestHandler"))
    {
        _logger.setLevel(Poco::Message::PRIO_TRACE);
        //_logger.trace(__PRETTY_FUNCTION__);
    }

    RequestRequestHandler::~RequestRequestHandler()
    {
        //_logger.trace(__PRETTY_FUNCTION__);
    }

    void RequestRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        NameValueCollection messages;
        string username;
        string password;
        bool error = false;

        try {
#if 0
            if( request.getMethod() == "GET") {
                throw UnexpectedArgumentException("RequestRequestHandler called with GET method.");
            }

            HTMLForm form(request, request.stream());
            if( ! request.has("username") ) {
                throw MissingArgumentException("username is missing");
            }
            if( ! request.has("password") ) {
                _logger.information("password is empty");
                throw MissingArgumentException("password is missing");
            }
#endif
#if 0
            string username = form["username"];
            string password = form["password"];
            if( username.empty() ) {
                _logger.information("username is empty");
                response.add("username-error", "username cannot be empty");
                error = true;
            }
            if( password.empty() ) {
                _logger.information("password is empty");
                response.add("password-error", "password cannot be empty");
                error = true;
            }
#endif // 0

        } catch( OptionException e ) {
            _logger.information(e.className());
            _logger.information(e.message());
            error = true;
        } catch( Poco::Exception e ) {
            _logger.information(e.className());
            _logger.information(e.message());
            error = true;
        } catch( ... ) {
            _logger.error("Unknown exception");
            error = true;
        }

        if(error) {
            _logger.trace("error: Sending to IndexHandler");
            write(request,response);
            return;
        }

        _logger.trace("Sending to VerifyHandler");
        unique_ptr<JclPageRequestHandler> hp { new VerifyHandler() };
        hp->handleRequest(request, response);
    }


    void RequestRequestHandler::write(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        _logger.trace(__PRETTY_FUNCTION__);

        Page page("Request", request, response);
        page.setFormData(_formData);

#if 1
        TextContent* text1 = new TextContent(page);
        text1->setText("<p>Some Text</p>");

        TextContent* text2 = new TextContent(page);
        text2->setText("<p>More Text</p>");

        TextContent* text3 = new TextContent(page);
        text3->setText("<p>End Text</p>");
#endif

        page.add(new HeaderContent(page));
        page.add(new RequestContent(page));
        page.add(new FooterContent(page));
#if 0
        page.addAfter("Header", text1);
        page.addAfter("Request", text2);
        page.addAfter("Footer", text3);
#endif
        page.send();

    }


}
    
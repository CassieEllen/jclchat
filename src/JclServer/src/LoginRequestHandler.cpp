// LoginRequestHandler.cpp
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

#include <JclServer/LoginRequestHandler.hpp>

#include <JclServer/JclPage.hpp>
#include <JclServer/LoginContent.hpp>
#include <JclServer/HeaderContent.hpp>
#include <JclServer/FooterContent.hpp>
#include <JclServer/TextContent.hpp>

#include <HtmlPages/VerifyHandler.h>
#include <HtmlPages/LoginHandler.h>
#include <HtmlPages/IndexHandler.h>

#include <Poco/Logger.h>

#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/OptionException.h>

#include <memory>


namespace jcl {
    using namespace std;
    using namespace Poco::Net;
    using Poco::Util::OptionException;
    using Poco::Util::MissingArgumentException;
    using Poco::Util::UnexpectedArgumentException;
    
    LoginRequestHandler::LoginRequestHandler()
        : _logger(Poco::Logger::get("LoginRequestHandler"))
    {
        _logger.setLevel(Poco::Message::PRIO_TRACE);
        _logger.trace(__PRETTY_FUNCTION__);
    }

    LoginRequestHandler::~LoginRequestHandler()
    {
        _logger.trace(__PRETTY_FUNCTION__);
    }

    void LoginRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        NameValueCollection messages;
        string username;
        string password;
        bool error = false;

        try {
            if( request.getMethod() == "GET") {
                throw UnexpectedArgumentException("LoginRequestHandler called with GET method.");
            }

            HTMLForm form(request, request.stream());
            if( ! request.has("username") ) {
                throw MissingArgumentException("username is missing");
            }
            if( ! request.has("password") ) {
                _logger.information("password is empty");
                throw MissingArgumentException("password is missing");
            }
            
#if 1
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
            //unique_ptr<JclPageRequestHandler> hp { new IndexHandler() };
            //hp->handleRequest(request, response);
            write(request,response);
            return;
        }

        _logger.trace("Sending to VerifyHandler");
        unique_ptr<JclPageRequestHandler> hp { new VerifyHandler() };
        hp->handleRequest(request, response);
    }


    void LoginRequestHandler::write(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        _logger.trace(__PRETTY_FUNCTION__);

        JclPage page("Login");

        TextContent* text1 = new TextContent;
        text1->setText("<p>Some Text</p>");

        TextContent* text2 = new TextContent;
        text2->setText("<p>More Text</p>");

        TextContent* text3 = new TextContent;
        text3->setText("<p>End Text</p>");

        page.add(new HeaderContent);
        page.add(new LoginContent);
        page.add(new FooterContent);
        page.addAfter("Header", text1);
        page.addAfter("Login", text2);
        page.addAfter("Footer", text3);
        
        page.send(request, response);
        
    }
    
}


// VerifyRequestHandler.cpp
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

#include <JclServer/VerifyRequestHandler.hpp>

#include <JclServer/Page.hpp>
#include <JclServer/VerifyContent.hpp>
#include <JclServer/HeaderContent.hpp>
#include <JclServer/FooterContent.hpp>
#include <JclServer/TextContent.hpp>

namespace jcl {
    using namespace std;
    using namespace Poco::Net;
    using Poco::Logger;
    //using Poco::URI;
    //using Poco::Util::OptionException;
    //using Poco::Util::MissingArgumentException;
    //using Poco::Util::UnexpectedArgumentException;

    VerifyRequestHandler::VerifyRequestHandler()
        : _logger(Logger::get("VerifyRequestHandler"))
    {
        //_logger.setLevel(Poco::Message::PRIO_TRACE);
        _logger.trace(__PRETTY_FUNCTION__);
    }

    VerifyRequestHandler::~VerifyRequestHandler()
    {
        _logger.trace(__PRETTY_FUNCTION__);
    }

    void VerifyRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        _logger.trace(__PRETTY_FUNCTION__);

        write(request, response);
    }
        
    void VerifyRequestHandler::write(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        _logger.trace(__PRETTY_FUNCTION__);

        Page page("Verify", request, response);

        page.add( make_shared<VerifyContent>() );

        page.send();
        
    }
    
}
    
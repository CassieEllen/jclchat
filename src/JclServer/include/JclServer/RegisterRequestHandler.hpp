// RegisterRequestHandler.hpp
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

#ifndef RegisterRequestHandler_INCLUDED
#define RegisterRequestHandler_INCLUDED

#include <JclServer/Types.hpp>

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Logger.h>

namespace jcl {

class RegisterRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
    RequestRequestHandler();
    RequestRequestHandler(const RequestRequestHandler&) = delete;
    RequestRequestHandler& operator=(const RequestRequestHandler&) = delete;
    virtual ~RequestRequestHandler();

    virtual void handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp);
    void write(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp);

private:

    Poco::Logger& _logger;
    NameValueCollection _formData;
};

}
#endif // RegisterRequestHandler_INCLUDED

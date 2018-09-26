// LoginRequestHandler.hpp
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

#ifndef LoginRequestHandler_INCLUDED
#define LoginRequestHandler_INCLUDED

#include <JclServer/Types.hpp>

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Logger.h>

namespace jcl {

class LoginRequestHandler : public Poco::Net::HTTPRequestHandler
{
 public:
    /// @brief
    LoginRequestHandler();

    /// @brief
    virtual ~LoginRequestHandler();

    /// @brief
    LoginRequestHandler(const LoginRequestHandler&) = delete;

    /// @brief
    /// @return
    LoginRequestHandler& operator=(const LoginRequestHandler&) = delete;

    /// @brief
    /// @param req
    /// @param resp
    virtual void handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp);

    /// @brief
    /// @param req
    /// @param resp
    void write(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp);
    
 private:

    /// @brief
    Poco::Logger& _logger;

    /// @brief
    NameValueCollection _formData;
};

}
#endif // LoginRequestHandler_INCLUDED

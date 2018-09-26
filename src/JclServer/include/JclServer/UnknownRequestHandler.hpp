// UnknownRequestHandler.hpp
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

#ifndef UnknownRequestHandler_INCLUDED
#define UnknownRequestHandler_INCLUDED

#include <JclServer/Types.hpp>
#include <JclServer/PageContent.hpp>

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Logger.h>

namespace jcl {
  
class UnknownContent : public PageContent
{
public:
    UnknownContent();
    virtual ~UnknownContent() = default;
    UnknownContent(const UnknownContent&) = delete;
    UnknownContent&operator=(const UnknownContent&) = delete;

    std::ostream& write(std::ostream& os) const override;
    std::ostream& write(std::ostream& os) override;
};

class UnknownRequestHandler : public Poco::Net::HTTPRequestHandler
{
 public:
    UnknownRequestHandler();
    UnknownRequestHandler(const UnknownRequestHandler&) = delete;
    UnknownRequestHandler& operator=(const UnknownRequestHandler&) = delete;
    virtual ~UnknownRequestHandler() = default;

    virtual void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
    void write(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
    
 private:

    Poco::Logger& _logger;
    //NameValueCollection _formData;
};

}
#endif // UnknownRequestHandler_INCLUDED

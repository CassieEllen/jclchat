// FileRequestHandler.hpp
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

#ifndef FileRequestHandler_INCLUDED
#define FileRequestHandler_INCLUDED

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Logger.h>

#include <boost/filesystem.hpp>

namespace jcl {

class FileRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
    FileRequestHandler();
    virtual ~FileRequestHandler() = default;
    FileRequestHandler(const FileRequestHandler&) = delete;
    FileRequestHandler& operator=(const FileRequestHandler&) = delete;

    void handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp) override ;
    void write(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp);
    void writeFileDoesNotExist(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp);
    void writeException(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp);

 private:
    void getContentType(const boost::filesystem::path& path);

    void displayHeaderRecords(const Poco::Net::HTTPServerResponse &response) const;

    Poco::Logger& _logger;
    boost::filesystem::path _path;
    std::string _contentType;

};

}
#endif // FileRequestHandler_INCLUDED

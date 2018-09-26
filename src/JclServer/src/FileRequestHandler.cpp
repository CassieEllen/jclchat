// FileRequestHandler.cpp
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

#include <JclServer/FileRequestHandler.hpp>

#include <Poco/Util/Application.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/File.h>
#include "Poco/URI.h"
#include <Poco/Exception.h>

#include <iostream>
#include <regex>
#include <map>
#include <memory>
#include <unistd.h>
#include <fstream>
#include <JclServer/JclServerApp.hpp>

namespace jcl {
    using namespace std;
    using namespace Poco::Net;
    using namespace boost::filesystem;

    FileRequestHandler::FileRequestHandler()
        : _logger(Poco::Logger::get("HTTPRequestHandler.FileRequestHandler"))
        , _path()
        , _contentType()
    {
        string level = Poco::Util::Application::instance().config().getString("application.log_level", "none");
        _logger.setLevel(level);

        _logger.trace(__PRETTY_FUNCTION__);
    }

    void FileRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        _logger.trace(__PRETTY_FUNCTION__);

        try {
            Poco::URI uri {request.getURI()};
            _logger.information("uri: " + uri.toString() );
            auto filePath = uri.getPath().substr(1);
            _logger.information("filePath: " + filePath);

            getContentType(filePath);

            auto& app = JclServerApp::instance();
            _path = app.getAppPath().toString();
            _path /= filePath;
            _logger.information("_path: " + _path.string());

#if 0
            string cmd { "ls -l " };
            cmd.append( _path.string() );
            system(cmd.c_str());
#endif

            if( ! exists(_path) ) {
                _logger.error("Application path: " + Poco::Util::Application::instance().commandPath() );
                throw Poco::FileNotFoundException("File not found: " + _path.string() );
            }

            //_logger.trace("File found: " + _path.string() );
            write(request, response);
            return;

        } catch (const Poco::FileNotFoundException& e) {
            _logger.log(e, __FILE__, __LINE__);
            //_logger.error(__FILE__ + __LINE__);
            _logger.error("Exception: " + e.message());
            _logger.error(e.className());
            writeFileDoesNotExist(request, response);
        } catch (const Poco::Exception& e) {
            _logger.log(e, __FILE__, __LINE__);
            _logger.error(__FILE__ + __LINE__);
            _logger.error("Exception: " + e.message());
            _logger.error(e.className());
            writeException(request, response);
        }
    }

    void FileRequestHandler::getContentType(const path& path)
    {
        _logger.trace(__PRETTY_FUNCTION__);
        regex extPattern(".*\\.(.*)$");
        smatch m;
        bool found = regex_match(path.string(), m, extPattern);
        if( ! found) {
            throw Poco::Exception("pattern not found", __FILE__, __LINE__);
        } else if( m.size() != 2 ) {
            throw Poco::Exception("pattern not found - count not 2", __FILE__, __LINE__);
        }
        string ext = m[1].str();
        //_logger.information("ext: " + ext);

        map<string,string> contentMap {
                {"css", "text/css"},
                {"ico", "image/x-icon"},
                {"js", "text/javascript"}
        };
        auto mit = contentMap.find(ext);
        if(mit == contentMap.end()) {
            _logger.error("Content type not found.");
            throw Poco::Exception("Content-type not found for extension: " + ext, __FILE__, __LINE__);
        }
        _contentType = mit->second;
        _logger.information("_contentType: "  +_contentType);
    }

    void FileRequestHandler::writeFileDoesNotExist(HTTPServerRequest &request, HTTPServerResponse &response) {
        _logger.trace(__PRETTY_FUNCTION__);
        _logger.trace("_contentType: " + _contentType);
        _logger.information("File not found: " + _path.string());

        response.setStatus(HTTPResponse::HTTP_NOT_FOUND);
        response.setContentType("text/plain");
        ostream &out = response.send();
        out << "Not found: " << _path << endl;
        out.flush();
        displayHeaderRecords(response);
    }

    void FileRequestHandler::writeException(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        _logger.trace(__PRETTY_FUNCTION__);
        _logger.trace("_contentType: " + _contentType);
        _logger.information("Exception thrown trying to send: " + _path.string());

        response.setStatus(HTTPResponse::HTTP_NOT_IMPLEMENTED);
        response.setContentType("text/plain");
        ostream &out = response.send();
        out << "Exception thrown trying to send: " << _path << endl;
        out.flush();
        displayHeaderRecords(response);
    }

    void FileRequestHandler::write(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        _logger.trace(__PRETTY_FUNCTION__);
        _logger.trace("_contentType: " + _contentType);
        displayHeaderRecords(response);

        if (_contentType.empty()) {
            _logger.information("_contentType is empty");
            response.setStatus(HTTPResponse::HTTP_NOT_FOUND);
            response.setContentType("text/plain");
            ostream& out = response.send();
            out << "Not Implemented: " << _contentType << endl;
            out << _path << endl;
            out.flush();
            return;
        }

        try {
            _logger.trace("Send file:" + _path.string());
            response.sendFile(_path.string(), _contentType);
        } catch(const Poco::Exception& e) {
            _logger.debug(e.className());
            _logger.debug(e.message());
        }

    }

    void FileRequestHandler::displayHeaderRecords(const HTTPServerResponse &response) const {
        // Display header records
        _logger.information("Header Records:");
        for(auto it : response) {
            _logger.information("\t" + it.first + ": " + it.second);
        }
    }

} // namespace jcl
    

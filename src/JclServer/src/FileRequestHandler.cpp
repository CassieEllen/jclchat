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

namespace jcl {
    using namespace std;
    using namespace Poco::Net;
    using namespace boost::filesystem;

    FileRequestHandler::FileRequestHandler()
        : _logger(Poco::Logger::get("HTTPRequestHandler.FileRequestHandler"))
        , _path()
        , _contentType()
    {
        _logger.setLevel(Poco::Message::PRIO_TRACE);
        _logger.trace(__PRETTY_FUNCTION__);
    }

    void FileRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        _logger.trace(__PRETTY_FUNCTION__);

        try {
            Poco::URI uri {request.getURI()};
            _logger.information("uri: " + uri.toString() );
            auto filePath = uri.getPath().substr(1);


            getContentType(filePath);


            _path = current_path();
            _path /= filePath;

#if 0
            string cmd { "ls -l " };
            cmd.append( _path.string() );
            system(cmd.c_str());
#endif

            if( ! exists(_path) ) {
                //cout << Poco::Util::Application::instance().commandPath() << endl;
                throw Poco::FileNotFoundException("File not found: " + _path.string() );
            }

            _logger.trace("File found: " + _path.string() );
            write(request, response);
            return;

        } catch (const Poco::FileNotFoundException& e) {
            _logger.error(__FILE__ + __LINE__);
            _logger.error("Exception: " + e.message());
            _logger.error(e.className());
        } catch (const Poco::Exception& e) {
            _logger.error(__FILE__ + __LINE__);
            _logger.error("Exception: " + e.message());
            _logger.error(e.className());
        }
        
        write(request, response);
    }

    void FileRequestHandler::getContentType(const path& path)
    {
        _logger.trace(__PRETTY_FUNCTION__);
        regex extPattern(".*\\.(.*)$");
        smatch m;
        bool found = regex_match(path.string(), m, extPattern);
        if( ! found) {
            throw Poco::Exception("pattern not found", __FILE__, __LINE__);
        }
        if( m.size() != 2 ) {
#if 0
            cout << "size: " << m.size() << endl;
            for(auto i : m) {
                cout << "\t" << i.str() << endl;
            }
#endif
            throw Poco::Exception("pattern not found - count not 2", __FILE__, __LINE__);
        }
        string ext = m[1].str();
        _logger.information("ext: " + ext);

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

    void FileRequestHandler::write(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        _logger.trace(__PRETTY_FUNCTION__);
        _logger.trace("_contentType: " + _contentType);

        if (_contentType.empty()) {
            response.setStatus(HTTPResponse::HTTP_NOT_FOUND);
            response.setContentType("text/plain");
            ostream& out = response.send();
            out << "Not Implemented: " << _contentType << endl;
            out << "\"" << _path << "\"" << endl;
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

}
    

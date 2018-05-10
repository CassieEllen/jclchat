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
#include "Poco/Path.h"
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
        : _logger(Poco::Logger::get("FileRequestHandler"))
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
            cout << "uri: " << uri.toString() << endl;
            auto filePath = uri.getPath().substr(1);
            cout << "filePath: " << filePath << endl;

            getContentType(filePath);
            _logger.trace("after getContentType()");

            cout << "current_path(): " << current_path() << endl;
            _path = current_path();
            cout << "_path: " << _path << endl;
            _path /= filePath;
            cout << "_path: " << _path << endl;


            if( ! exists(_path) ) {
                cout << Poco::Util::Application::instance().commandPath() << endl;
                throw Poco::Exception("File not found: " + _path.string() );
            }
            _logger.trace("File found: " + _path.string() );
            write(request, response);

        } catch (const Poco::Exception& e) {
            _logger.error("Exception: " + e.message());
        }
        
        write(request, response);
    }

    void FileRequestHandler::write(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        _logger.trace(__PRETTY_FUNCTION__);
        _logger.trace("_contentType: " + _contentType);

        if (_contentType.empty()) {
            response.setStatus(HTTPResponse::HTTP_NOT_FOUND);
            response.setContentType("text/plain");
            ostream& out = response.send();
            out << "Not Implemented";
            out.flush();
            return;
        }

        try {
            _logger.trace("Send file:" + _path.string());
            response.sendFile(_path.string(), _contentType);
            ifstream is(_path.string(), std::ios::binary);
        } catch(Poco::Exception& e) {
            _logger.debug(e.message());
        }

    }

    void FileRequestHandler::getContentType(const path& path)
    {
        _logger.trace(__PRETTY_FUNCTION__);
        regex extPattern(".*\\.(.*)$");
        smatch m;
        cout << "path: " << path << endl;
        bool found = regex_match(path.string(), m, extPattern);
        if( ! found) {
            throw Poco::Exception("pattern not found");
        }
        if( m.size() != 2 ) {
            cout << "size: " << m.size() << endl;
            for(auto i : m) {
                cout << "\t" << i.str() << endl;
            }
            throw Poco::Exception("pattern not found - count not 2");
        }
        string ext = m[1].str();
        cout << "ext: " << ext << endl;
        
        map<string,string> contentMap { {"ico", "image/x-icon"} };
        auto mit = contentMap.find(ext);
        if(mit == contentMap.end()) {
            cout << "Content type not found." << endl;
            throw Poco::Exception("extension not found: " + ext);
        }
        _contentType = mit->second;
        cout << "_contentType: "  <<_contentType << endl;
        
    }

}
    

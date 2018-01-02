// JclRequestHandler.cpp
//
// <one line to give the program's name and a brief idea of what it does.>
// Copyright (C) 2017 Cassie E Nicol
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

#include <JclServer/JclRequestHandler.hpp>

#include <iostream>

namespace jcl {

    using namespace Poco::Net;
    using namespace std;
    
    int JclRequestHandler::count = 0;

    void JclRequestHandler::handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp)
    {
        resp.setStatus(HTTPResponse::HTTP_OK);
        resp.setContentType("text/html");

        ostream& out = resp.send();
        out << "<h1>Unhandled Response</h1>"
            << "<p>Count: "  << ++count         << "</p>"
            << "<p>Host: "   << req.getHost()   << "</p>"
            << "<p>Method: " << req.getMethod() << "</p>"
            << "<p>URI: "    << req.getURI()    << "</p>";
        out.flush();

        cout << endl
             << "Response sent for count=" << count
             << " and URI=" << req.getURI() << endl;
    }


}

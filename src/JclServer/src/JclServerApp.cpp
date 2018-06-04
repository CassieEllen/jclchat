// JclServerApp.cpp
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

#include <JclServer/JclServerApp.hpp>
#include <JclServer/JclRequestHandlerFactory.hpp>

#include <Poco/Message.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Util/LayeredConfiguration.h>

#include <boost/lexical_cast.hpp>

#include <iostream>
#include <system_error>

namespace jcl {

    using namespace Poco::Net;
    using namespace std;
    using namespace Poco;
    using boost::lexical_cast;
    using boost::bad_lexical_cast;


    JclServerApp::JclServerApp()
        : _model(Model::instance())
        , ServerApplication()
    {
    }

    Model& JclServerApp::model()
    {
        return _model;
    }

    int JclServerApp::main(const std::vector<std::string> &)
    {
        HTTPServer s(new JclRequestHandlerFactory(_model), ServerSocket(9090), new HTTPServerParams);

        auto& configuration = config();

        string app_path = configuration.getString("application.path");
        cout << "app.path = " << app_path << endl;

        string dbName = configuration.getString("mysql.host");
        cout << "Host: " << dbName << endl;

        s.start();
        cout << endl << "Server started" << endl;

        waitForTerminationRequest();  // wait for CTRL-C or kill

        cout << endl << "Shutting down..." << endl;
        s.stop();

        return Application::EXIT_OK;
    }

    void JclServerApp::initialize(Application& self)
    {
        loadConfiguration();
        Application::initialize(self);
        logger().setLevel(Poco::Message::Priority::PRIO_TRACE);
        //logger().setLevel(Message::Priority::PRIO_DEBUG);
        _model.configure(config());
        cout << _model.toString() << endl;
        string connectString = _model.getConnectString();
        cout << "Connect String: " << connectString << endl;
        string host;
        string port;
        try {
            host = config().getString("web.host");
            //cout << "web.host: " << host << endl;
            port = config().getString("web.port");
            //cout << "web.port: " << port << endl;
        } catch(NotFoundException& e) {
            cerr << e.className() << ": " << e.message() << endl;
            cerr << R"msg(
Your jclchat.ini file is not configured properly. Please check the
[web] section and ensure that 'base', 'host', and 'port' are all
defined.

)msg";
            throw system_error(error_code(), "Invalid configuration");
        }
        //cout << "web.host: " << host << endl;
        //cout << "web.port: " << port << endl;
        string path = "http://" + host;
        port.insert(0, ":");
        //cout << "path: " << path << endl;
        _httpPath.setPath(path);
        _pocoPath.setPath(path + port);
        cout << "_httpPath: " << _httpPath.getPath() << endl;
        cout << "_pocoPath: " << _pocoPath.getPath() << endl;
    }

    string JclServerApp::getWebPath() const
    {
        return config().getString("web.base");
    }

    const Poco::URI &JclServerApp::getHttpPath() const {
        return _httpPath;
    }

    const Poco::URI &JclServerApp::getPocoPath() const {
        return _pocoPath;
    }

}

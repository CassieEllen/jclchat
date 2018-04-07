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

#include <Poco/Net/HTTPServer.h>
#include <Poco/Util/LayeredConfiguration.h>

#include <iostream>

namespace jcl {

    using namespace Poco::Net;
    using namespace std;

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
        _model.configure(config());
        cout << _model.toString() << endl;
        string connectString = _model.getConnectString();
        cout << "Connect String: " << connectString << endl;
    }

    string JclServerApp::getWebPath()
    {
        return config().getString("web.base");
    }
}

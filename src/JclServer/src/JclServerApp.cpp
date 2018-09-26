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
#include <JclModel/Model.hpp>

#include <Poco/Message.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Util/LayeredConfiguration.h>

#include <Poco/SimpleFileChannel.h>

#include <boost/lexical_cast.hpp>

#include <iostream>
#include <system_error>

namespace jcl {

    using namespace Poco::Net;
    using namespace std;
    using namespace Poco;
    using boost::lexical_cast;
    using boost::bad_lexical_cast;

    /***
    Logging Levels (std::string)
    none (turns off logging)
    fatal
    critical
    error
    warning
    notice
    information
    debug
    trace

     Logging Levels (int)
     PRIO_FATAL
     PRIO_CRITICAL
     PRIO_ERROR
     PRIO_WARNING
     PRIO_NOTICE
     PRIO_INFORMATION
     PRIO_DEBUG
     PRIO_TRACE
    ***/


    JclServerApp::JclServerApp()
            : _model(), _httpPath(), _pocoPath(), _appPath(), _logLevel("error") {

        if (config().getBool("application.runAsDaemon", false)) {
            // do daemon specific things
            cout << "Running as a daemon" << endl;
        }

        AutoPtr<SimpleFileChannel> pChannel(new SimpleFileChannel);
        pChannel->setProperty("path", "chat.log");
        //pChannel->setProperty("rotation", "2 K");
        pChannel->setProperty("rotation", "never");
        pChannel->setProperty("flush", "true");
        Logger::root().setChannel(pChannel);
        Logger &rootLogger = Logger::get("JclChat"); // inherits root channel

        setLogger(rootLogger);

        logger().setLevel(Poco::Message::Priority::PRIO_TRACE);
        //logger().setLevel(Message::Priority::PRIO_DEBUG);
        logger().trace(__PRETTY_FUNCTION__);
    }

    /// @brief Get the application's name.
    /// @return the application's name.
    const char *JclServerApp::name() const {
        return "JclChat";
    }

    /// @brief Gets application path
    ///
    /// This path is where the application was initially loaded. It is used to find the source files
    /// Under the server directory. This path is important when running as a daemon.
    ///
    /// @return POCO server application path
    const Poco::URI &JclServerApp::getAppPath() const {
        return _appPath;
    }

    void JclServerApp::initialize(Application &self) {
        loadConfiguration();
        Application::initialize(self);

#if 0
        _model.configure(config());
        cout << _model.toString() << endl;
        string connectString = _model.getConnectString();
        cout << "Connect String: " << connectString << endl;
#endif
        string host;
        string port;
        try {
            host = config().getString("web.host");
            port = config().getString("web.port");
        } catch (NotFoundException &e) {
            cerr << e.className() << ": " << e.message() << endl;
            cerr << R"msg(
Your jclchat.ini file is not configured properly. Please check the
[web] section and ensure that 'base', 'host', and 'port' are all
defined.

)msg";
            throw system_error(error_code(), "Invalid configuration");
        }
        string path = "http://" + host;
        port.insert(0, ":");
        _httpPath.setPath(path);
        _pocoPath.setPath(path + port);
        cout << "_httpPath: " << _httpPath.getPath() << endl;
        cout << "_pocoPath: " << _pocoPath.getPath() << endl;
    }


    Model& JclServerApp::model() {
        return _model;
    }

    int JclServerApp::main(const std::vector<std::string> &) {
        HTTPServer s(new JclRequestHandlerFactory(_model), ServerSocket(9090), new HTTPServerParams);

        auto &configuration = config();

#if 1
        _logLevel = config().getString("application.log_level", "none");
        logger().setLevel(_logLevel);
        cout << "loglevel: " << _logLevel << endl;
#endif

        _appPath = config().getString("application.dir");
        cout << "_appPath = " << _appPath.toString() << endl;
        logger().trace("_appPath: " + _appPath.toString());

        string dbName = configuration.getString("mysql.host");
        cout << "Host: " << dbName << endl;

        s.start();
        cout << endl << "Server started" << endl;
        logger().trace("Server started");

        waitForTerminationRequest();  // wait for CTRL-C or kill

        cout << endl << "Shutting down..." << endl;
        logger().trace("Shutting down...");
        s.stop();

        return Application::EXIT_OK;
    }

    string JclServerApp::getWebPath() const {
        return config().getString("web.base");
    }

    const Poco::URI &JclServerApp::getHttpPath() const {
        return _httpPath;
    }

    const Poco::URI &JclServerApp::getPocoPath() const {
        return _pocoPath;
    }

    void JclServerApp::uninitialize() {

    }

    void JclServerApp::reinitialize(Poco::Util::Application&) {

    }

    void JclServerApp::defineOptions(Poco::Util::OptionSet&) {

    }

}

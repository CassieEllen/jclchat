// Model.cpp
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

#include <JclModel/Model.hpp>

#include "Poco/Exception.h"
#include "Poco/Data/Session.h"

#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"

#include <Poco/Util/LayeredConfiguration.h>

#include <iostream>
#include <sstream>

namespace jcl {
    using namespace std;
    using Poco::Util::LayeredConfiguration;
    using namespace Poco::Data::Keywords;
    using Poco::Data::Session;
    using Poco::Data::Statement;

    /// @brief Default ctor
    Model::Model()
            : _host("localhost"),
              _port("3306"),
              _database("jcl"),
              _user("jcl"),
              _password("secret"),
              _compress("true"),
              _reconnect("true") {
        Poco::Data::MySQL::Connector::registerConnector();
    }

    /// @brief ctor using application configuration
    /// @param config application configuration
    Model::Model(const Poco::Util::LayeredConfiguration &config)
            : _host("localhost"),
              _port("3306"),
              _database("jcl"),
              _user("jcl"),
              _password("secret"),
              _compress("true"),
              _reconnect("true") {
        configure(config);
        Poco::Data::MySQL::Connector::registerConnector();
    }

    /// Destructor
    Model::~Model() {
        Poco::Data::MySQL::Connector::unregisterConnector();
    }

    /// Implements this class as a singleton managed by the application
    Model &Model::instance() {
        static Poco::SingletonHolder<Model> sh;
        return *sh.get();
    }

    void Model::configure(const Poco::Util::LayeredConfiguration &config) {
        _host = config.getString("mysql.host", "localhost");
        _port = config.getString("mysql.port", "3306");
        _database = config.getString("mysql.database", "jcl");
        _user = config.getString("mysql.user", "jcl");
        _password = config.getString("mysql.password", "secret");
        _compress = config.getString("mysql.compress", "true");
        _reconnect = config.getString("mysql.auto-reconnect", "true");
    }

    string Model::toString() const {
        ostringstream ss;
        ss << "Model" << endl
           << "\tHost: " << _host << endl
           << "\tPort: " << _port << endl
           << "\tDatabase: " << _database << endl
           << "\tUser: " << _user << endl
           << "\tPassword: " << _password << endl
           << "\tCompress: " << _compress << endl
           << "\tAuto-reconnect: " << _reconnect;
        return ss.str();
    }

    string Model::getConnectString() const {
        char sc{';'};
        ostringstream ss;
        ss << "host=" << _host << sc
           << "port=" << _port << sc
           << "db=" << _database << sc
           << "user=" << _user << sc
           << "password=" << _password << sc
           << "compress=" << _compress << sc
           << "auto-reconnect=" << _reconnect << sc;
        return ss.str();
    }

    Session Model::getSession() {
        // create a session
        Session session("mysql", getConnectString());
        return session;
    }

}

//
// Created by cenicol on 7/13/18.
//
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


#include <JclModel/DbConnection.hpp>

#include <Poco/Util/Application.h>

#include <Poco/File.h>

#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"

#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/OptionCallback.h>

#include <Poco/Util/LayeredConfiguration.h>

#include <iostream>
#include <sstream>
#include <asio/detail/shared_ptr.hpp>


using Poco::Util::LayeredConfiguration;

using namespace std;
using namespace jcl;

using Poco::Util::Application;

class DbMain : public Application {

protected:
    void initialize(Poco::Util::Application &application) {
        this->config().setString("optionval", "defaultoption");
        this->loadConfiguration();
        Poco::Util::Application::initialize(application);
    }

    void uninitialize() {
        Poco::Util::Application::uninitialize();
    }

    void defineOptions(Poco::Util::OptionSet &optionSet) {
        Poco::Util::Application::defineOptions(optionSet);

        optionSet.addOption(
                Poco::Util::Option("optionval", "", "Some value")
                        .required(false)
                        .repeatable(true)
                        .argument("<the value>", true)
                        .callback(Poco::Util::OptionCallback<DbMain>(this, &DbMain::handleMyOpt))
        );
        optionSet.addOption(
                Poco::Util::Option("configfile", "c", "Configuration File")
                        .required(true)
                        .repeatable(false)
                        .argument("<configfile>", true)
                        .callback(Poco::Util::OptionCallback<DbMain>(this, &DbMain::handleConfigFile))
        );
    }

    void handleMyOpt(const std::string &name, const std::string &value) {
        std::cout << "Setting option " << name << " to " << value << std::endl;
        this->config().setString(name, value);
        std::cout << "The option is now " << this->config().getString(name) << std::endl;
    }

    void handleConfigFile(const std::string &name, const std::string &value) {
        std::cout << "Setting option " << name << " to " << value << std::endl;
        this->config().setString(name, value);
        this->_configFile = value;
        std::cout << "The option is now " << this->config().getString(name) << std::endl;
    }

    void showKeys(const string &name) {
        Poco::Util::LayeredConfiguration::Keys range;
        this->config().keys(name, range);

        cout << "Config " << name << endl;
        for (auto item : range) {
            string key{item};
            if (!name.empty()) {
                key.insert(0, name + ".");
            }
            try {
                cout << "\t" << key << ": ";
                if (this->config().has(key)) {
                    cout << this->config().getString(key);
                } else {
                    cout << "no-value";
                }
                cout << endl;
            } catch (const Poco::Exception &e) {
                cout << endl;
                cout << e.message() << endl;
                cout << e.className() << " " << e.what() << endl;
                cout << e.displayText() << endl;
            }
        }
    }

    void setupConnection(LayeredConfiguration &config) {
        string key{"MySql"};
        string host = this->config().getString("MySql.host");
        string port = this->config().getString("MySql.port");
        string db = this->config().getString("MySql.database");
        string user = this->config().getString("MySql.user");
        string password = this->config().getString("MySql.password");
        string compress = this->config().getString("MySql.compress");
        string reconnect = this->config().getString("MySql.auto-reconnect");

        ostringstream oss;
        oss << "host=" << host
            << ";port=" << port
            << ";db=" << db
            << ";user=" << user
            << ";password=" << password
            << ";compress=" << compress
            << ";auto-reconnect=" << reconnect;

        auto connection = make_shared<DbConnection>(

                        [] { Poco::Data::MySQL::Connector::registerConnector(); },
                        [] { Poco::Data::MySQL::Connector::unregisterConnector(); },
                        "MySQL",
                        oss.str()
                        //"host=localhost;port=3306;db=jcl;user=jcl;password=JclD@taAcc3ss;compress=true;auto-reconnect=true",
        );

        _dbConnection = connection;
        cout << "Connection String: " << _dbConnection->connectString() << endl;
    }

    int main(const std::vector<std::string> &arguments) {
        std::cout << "We are now in main." << endl;

        cout << "Args" << endl;
        for (const auto &arg : arguments) {
            cout << "\t" << arg.c_str() << endl;
        }

        Poco::File config(_configFile);
        if (!config.exists()) {
            cerr << "Configuration file \"" << config.path() << "\" does not exist." << endl;
            return EXIT_FAILURE;
        }
        loadConfiguration(_configFile);

        showKeys("");
        showKeys("MySql");

        setupConnection(this->config());
        return EXIT_OK;
    }

    string _configFile;
    shared_ptr<DbConnection> _dbConnection;
};

POCO_APP_MAIN(DbMain)


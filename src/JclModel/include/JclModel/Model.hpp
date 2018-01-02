// Model.h
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

#ifndef Model_INCLUDED
#define Model_INCLUDED

#include "Poco/SingletonHolder.h"
#include <Poco/Util/LayeredConfiguration.h>
#include "Poco/Data/Session.h"

#include <string>

namespace jcl {

    class Model
    {
    public:
        Model();
        Model(Poco::Util::LayeredConfiguration& config);
        Model(Model& rhs) = delete;
        Model(Model&& rvalue) = delete;
        Model& operator=(Model& rhs) = delete;
        Model& operator=(Model&& rvalue) = delete;
        ~Model();
        void configure(Poco::Util::LayeredConfiguration& config);
        
        std::string getConnectString() const;
        Poco::Data::Session getSession();
            
        std::string toString() const;

        /// Returns a reference to the Application singleton.
        ///
        /// Throws a NullPointerException if no Application instance exists.
        static Model& instance();

    private:
        void setup();

        std::string _host;
        std::string _port;
        std::string _database;
        std::string _user;
        std::string _password;
        std::string _compress;
        std::string _reconnect;
    };
}

#endif // Model_INCLUDED

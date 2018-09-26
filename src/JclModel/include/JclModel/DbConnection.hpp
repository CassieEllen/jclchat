// DbConnection.hpp
//
// Created by cenicol on 7/14/18.
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

#ifndef JCLCHAT_DBDCONNECTION_HPP
#define JCLCHAT_DBDCONNECTION_HPP


#include <functional>

using namespace std;

namespace jcl {

    class DbConnection {

    public:
        DbConnection(function<void(void)> registerConnector,
                     function<void(void)> unregisterConnector,
                     const string &&database,
                     const string &&connectString)

                : _registerConnector(registerConnector),
                  _unregisterConnector(unregisterConnector),
                  _database(database),
                  _connectString(connectString)
        {
        }

        // I don't want surprises from copying this data.
        DbConnection(const DbConnection &rhs) = delete;
        DbConnection& operator=(const DbConnection& rhs) = delete;
        DbConnection& operator=(DbConnection&& rhs) = delete;

#if 0
        DbConnection(const DbConnection &rhs);
#endif

#if 0
        DbConnection& operator=(const DbConnection& rhs);
#endif

#if 0
        DbConnection& operator=(DbConnection&& rhs);
#endif

        void registerConnector() const {
            _registerConnector();
        }

        void unregisterConnector() const {
            _unregisterConnector();
        }

        const string &database() const {
            return _database;
        }

        const string &connectString() const {
            return _connectString;
        }

    private:
        function<void(void)> _registerConnector;
        function<void(void)> _unregisterConnector;
        string _database;
        string _connectString;
    };


}

#endif //JCLCHAT_DBDCONNECTION_HPP

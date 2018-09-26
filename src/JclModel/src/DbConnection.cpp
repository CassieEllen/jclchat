// Model.cpp
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
// SPDX-License-Identifier:	GPL-3.0

#include <JclModel/DbConnection.hpp>

namespace jcl {

#if 0
    DbConnection::DbConnection(const jcl::DbConnection &rhs) {

    }
#endif

#if 0
    DbConnection &DbConnection::operator=(const DbConnection &rhs) {
        _registerConnector = rhs._registerConnector;
        _unregisterConnector = rhs._unregisterConnector;
        _database = rhs._database;
        _connectString = rhs._connectString;
    }
#endif

#if 0
    DbConnection &DbConnection::operator=(DbConnection &&rhs) {
        _registerConnector = std::move(rhs._registerConnector);
        _unregisterConnector = std::move(rhs._unregisterConnector);
        _database = std::move(rhs._database);
        _connectString = std::move(rhs._connectString);

        return *this;
    }
#endif

}

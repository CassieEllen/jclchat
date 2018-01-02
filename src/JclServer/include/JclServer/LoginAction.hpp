// LoginAction.h
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

#ifndef LoginAction_INCLUDED
#define LoginAction_INCLUDED

#include <JclServer/JclAction.hpp>


namespace jcl {
    class Model;
    
    class LoginAction : public JclAction
    {
    public:
        LoginAction(const Poco::Net::HTTPServerRequest& request, Model& model);
        virtual JclPageRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

    };

}

#endif // LoginAction_INCLUDED

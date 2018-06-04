// JclServerApp.hpp
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

#ifndef JclServerApp_INCLUDED
#define JclServerApp_INCLUDED

#include <JclModel/Model.hpp>

#include <Poco/Util/ServerApplication.h>
#include <Poco/URI.h>
#include <string>

namespace jcl {

    class JclServerApp : public Poco::Util::ServerApplication
    {
    public:
        JclServerApp();
        Model& model();
    
    protected:
        int main(const std::vector<std::string> &);
        void initialize(Application& self);

        /// @brief Gets the web root as specified in the config file.
        /// [web]
        ///     base = /path/to/web/base
        /// @return the base path to retrieve web files from.
        std::string getWebPath() const;

        const Poco::URI& getHttpPath() const;
        const Poco::URI& getPocoPath() const;

        Model& _model;
        Poco::URI _httpPath;
        Poco::URI _pocoPath;
    };

}

#endif // JclServerApp_INCLUDED

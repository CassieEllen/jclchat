/// @file JclServerApp.hpp
//
// Implements the Chat Server Application
//
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

#include <Poco/Util/ServerApplication.h>


#include <JclModel/Model.hpp>

#include <Poco/Util/OptionSet.h>

#include <Poco/URI.h>
#include <string>

namespace Poco {
    namespace Util {
        class OptionSet;
    }
}
using Poco::Util::OptionSet;

namespace jcl {

    class JclServerApp : public Poco::Util::ServerApplication {
    public:
        JclServerApp();

        const char *name() const override;

        static JclServerApp &instance() {
            dynamic_cast<JclServerApp &>(Application::instance());
        }


        const Poco::URI &getAppPath() const;

    protected:
        void initialize(Application &app) override;

        void uninitialize() override;

        void reinitialize(Application &app) override;

        void defineOptions(OptionSet &options) override;


        Model &model();

        /// @brief Gets the web root as specified in the config file.
        /// [web]
        ///     base = /path/to/web/base
        /// @return the base path to retrieve web files from.
        std::string getWebPath() const;

        /// @brief Gets the URI of apache2 running on the same server
        /// @return Apache2 URI
        const Poco::URI &getHttpPath() const;

        /// @brief Gets the URI of the poco server
        /// @return POCO server URI
        const Poco::URI &getPocoPath() const;


    protected:
        int main(const std::vector<std::string> &) override;

        Model _model;
        Poco::URI _httpPath;
        Poco::URI _pocoPath;
        Poco::URI _appPath;
        std::string _logLevel;

    };

} // namespace jcl

#endif // JclServerApp_INCLUDED

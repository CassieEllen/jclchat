// WelcomeRequestHandler.cpp
//
// <one line to give the program's name and a brief idea of what it does.>
// Copyright (C) 2018 Cassie E Nicol
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

#include <JclServer/WelcomeRequestHandler.hpp>

#include <JclServer/Page.hpp>
#include <JclServer/TextContent.hpp>

#include <Poco/Util/Application.h>

#include <iostream>

namespace jcl {
    using namespace std;
    using namespace Poco::Net;

    WelcomeContent::WelcomeContent()
            : PageContent("Welcome") {
    }

    std::ostream &WelcomeContent::write(std::ostream &os) {
        auto& data = getData();

        string title = data.get("getPage.title", "Welcome");
        os << "<!-- " << __PRETTY_FUNCTION__ << " -->" << endl;

        os << R"msgx(
<p>Welcome Content</p>
<p><a href="login">login</a> or <a href="register">register</a>.</p>
        )msgx" << endl;
	return os;
    }

    //----------------------------------------------------------------------------------------------------------------

    WelcomeRequestHandler::WelcomeRequestHandler()
            : _logger(Poco::Logger::get("WelcomeRequestHandler"))
    {
        string level = Poco::Util::Application::instance().config().getString("application.log_level", "none");
        _logger.setLevel(level);

        _logger.trace(__PRETTY_FUNCTION__);
    }

    void WelcomeRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) {
        _logger.trace(__PRETTY_FUNCTION__);

        write(request, response);
    }

    void WelcomeRequestHandler::write(HTTPServerRequest &request, HTTPServerResponse &response) {
        _logger.trace(__PRETTY_FUNCTION__);

        Page page("Welcome", request, response);
        auto data = page.getFormData();
        data.set("getPage.title", "Welcome");
        data.set("getPage.h1", "Welcome to Chat");

        page.add( make_shared<WelcomeContent>());

        page.send();
    }

}
    

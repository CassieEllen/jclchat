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
#include <JclServer/HeaderContent.hpp>
#include <JclServer/FooterContent.hpp>
#include <JclServer/TextContent.hpp>

#include <iostream>

namespace jcl {
    using namespace std;
    using namespace Poco::Net;

    WelcomeContent::WelcomeContent(Page &page)
            : PageContent("Welcome", page) {
    }

    std::ostream &WelcomeContent::write(std::ostream &os) const {
        auto &data = _page.getFormData();

        string title = data.get("page.title", "Welcome");
        os << "<!-- " << __PRETTY_FUNCTION__ << " -->" << endl;

        os << R"msgx(
<p>Welcome Content</p>
<p><a href="login">login</a> or <a href="register">register</a>.</p>
        )msgx" << endl;
    }

    //----------------------------------------------------------------------------------------------------------------

    WelcomeRequestHandler::WelcomeRequestHandler()
            : _logger(Poco::Logger::get("WelcomeRequestHandler"))
    {
        _logger.setLevel(Poco::Message::PRIO_DEBUG);
        _logger.trace(__PRETTY_FUNCTION__);
    }

    void WelcomeRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) {
        _logger.trace(__PRETTY_FUNCTION__);

        write(request, response);
    }

    void WelcomeRequestHandler::write(HTTPServerRequest &request, HTTPServerResponse &response) {
        _logger.trace(__PRETTY_FUNCTION__);

        Page page("Welcome", request, response);
        auto &data = page.getFormData();
        data.set("page.title", "Welcome");
        data.set("page.h1", "Welcome to Chat");

        page.add(new HeaderContent(page));
        page.add(new WelcomeContent(page));
        page.add(new FooterContent(page));

        page.send();
    }

}
    
// WelcomeRequestHandler.hpp
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

#ifndef WelcomeRequestHandler_INCLUDED
#define WelcomeRequestHandler_INCLUDED

#include <JclServer/PageContent.hpp>

#include <JclServer/Types.hpp>

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Logger.h>

namespace jcl {

    /// @brief Welcome Page Content
    ///
    class WelcomeContent : public PageContent
    {
    public:
        explicit WelcomeContent(Page& page);
        virtual ~WelcomeContent() override = default;

        std::ostream& write(std::ostream& os) const override;
    };

    /// @brief Welcome Page Request Handler
    class WelcomeRequestHandler : public Poco::Net::HTTPRequestHandler
    {
    public:
        WelcomeRequestHandler();
        virtual ~WelcomeRequestHandler() = default;
        WelcomeRequestHandler(const WelcomeRequestHandler&) = delete;
        WelcomeRequestHandler& operator=(const WelcomeRequestHandler&) = delete;

        void handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp) override;
        void write(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp);

    private:

        Poco::Logger& _logger;
    };

}

#endif // WelcomeRequestHandler_INCLUDED

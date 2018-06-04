/// @file Page.hpp
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

#ifndef Page_INCLUDED
#define Page_INCLUDED

#include <JclServer/PocoClasses.hpp>

#include <Poco/Logger.h>
#include <Poco/Net/NameValueCollection.h>

#include <memory>
#include <string>
#include <vector>


namespace jcl {

    class PageContent;

    /// Provides the functionality of an HTML page.
    class Page {
    public:
        /// @brief Constructor
        /// @param name
        /// @param request
        /// @param response
        Page(const std::string &name, Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

        /// @brief Destructor
        virtual ~Page();

        /// @brief Do not allow copying
        Page(const Page&) = delete;

        /// @brief Disable operater=
        /// @return does not get executed
        Page& operator=(const Page&) = delete;

        /// @brief Send the page.
        void send();

        /// @brief Add content to the end of the content list.
        /// @param content content to be added
        void add(PageContent *content);

        /// @brief Add content after the named content.
        /// @param name
        /// @param content
        void addAfter(const std::string &name, PageContent *content);

        /// @brief Get the page name
        /// @return the page name
        const std::string &getName() const {
            return _name;
        }

        /// @brief Set the page name
        /// @param name name of the page
        void setName(const std::string &name) {
            _name = name;
        }

        /// @brief Get the page variables
        /// @return NameValueCollection containg the form data;
        Poco::Net::NameValueCollection &getFormData() {
            return _formData;
        }

        /// @brief Set the page variables
        /// @param data
        void setFormData(const Poco::Net::NameValueCollection &data) {
            _formData = data;
        }

        /// @brief Get the HTTPServerRequest
        /// @return
        Poco::Net::HTTPServerRequest &getRequest() {
            return _request;
        }

        /// Get the HTTPServerResponse
        Poco::Net::HTTPServerResponse &getReponse() const {
            return _response;
        }

    private:
        /// @brief Name of page
        std::string _name;

        /// @brief Client Request
        Poco::Net::HTTPServerRequest &_request;

        /// @brief Client Response
        Poco::Net::HTTPServerResponse &_response;

        /// @brief Page variables sent to the content
        mutable Poco::Net::NameValueCollection _formData;

        /// @brief Page content vector
        std::vector<std::shared_ptr<PageContent> > _content;

        Poco::Logger& _logger;
    };

}
#endif // Page_INCLUDED

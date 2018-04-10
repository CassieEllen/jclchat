// Page.hpp
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

#include <Poco/Net/NameValueCollection.h>

#include <memory>
#include <string>
#include <vector>


namespace jcl {

    class PageContent;

    /// Provides the functionality of an HTML page.
    class Page {
    public:
        /// Constructor
        Page(const std::string &name, Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

        /// Destructor
        ~Page();

        /// Do not allow copying
        Page(const Page&) = delete;
        Page& operator=(const Page&) = delete;

        // Send the page.
        void send();

        // Add content to the end of the content list.
        void add(PageContent *content);

        // Add content after the named content.
        void addAfter(const std::string &name, PageContent *content);

        /// Get the page name
        const std::string &getName() const {
            return _name;
        }

        /// Set the page name
        void setName(const std::string &name) {
            _name = name;
        }

        /// Get the page variables
        const Poco::Net::NameValueCollection &getFormData() const {
            return _formData;
        }

        /// Set the page variables
        void setFormData(const Poco::Net::NameValueCollection &data) {
            _formData = data;
        }

        /// Get the HTTPServerRequest
        Poco::Net::HTTPServerRequest &getRequest() const {
            return _request;
        }

        /// Get the HTTPServerResponse
        Poco::Net::HTTPServerResponse &getReponse() const {
            return _response;
        }

    private:
        /// Name of page
        std::string _name;
        /// Client Request
        Poco::Net::HTTPServerRequest &_request;
        /// Client Response
        Poco::Net::HTTPServerResponse &_response;
        /// Page variables sent to the content
        mutable Poco::Net::NameValueCollection _formData;
        /// Page content vector
        std::vector<std::shared_ptr<PageContent> > _content;
    };

}
#endif // Page_INCLUDED

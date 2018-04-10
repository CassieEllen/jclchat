// UnknownRequestHandler.cpp
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

#include <JclServer/UnknownRequestHandler.hpp>

#include <JclServer/Page.hpp>
#include <JclServer/HeaderContent.hpp>
#include <JclServer/FooterContent.hpp>
#include <JclServer/TextContent.hpp>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/OptionException.h>


namespace jcl {
  using namespace std;
  using namespace Poco::Net;
  using Poco::Util::OptionException;
  using Poco::Util::MissingArgumentException;
  using Poco::Util::UnexpectedArgumentException;

    UnknownContent::UnknownContent(Page &page)
            : PageContent("Unknown", page) {
    }

    void UnknownContent::tableEntry(ostream& os, const std::string &key, const std::string &value) const
    {
        os << "<tr><th>" << key << "</th><td>" << value << "</td></tr>";
    }

    std::ostream &UnknownContent::write(std::ostream &os) const {
        os << R"msgx(<p>UnknownContent</p>)msgx" << endl;

        auto & request = _page.getRequest();

        // Display header records
        os << "<p>Header Records:</p>" << "<ul>";
        for (auto it : _page.getRequest()) {
            os << "<li>" << it.first << ": " << it.second << "</li>" << endl;
        }
        os << "</ul>";


        HTMLForm form(_page.getRequest(), _page.getRequest().stream());
        os << "<p>Form:</>" << "<ul>";
        for (auto it : form ) {
            os << "<li>" << it.first << ": " << it.second << "</li>" << endl;
        }
        os << "</ul>";

        NameValueCollection cookies;
        request.getCookies(cookies);
        os << "<p>Cookies:</>" << "<ul>";
        for (auto it : cookies ) {
            os << "<li>" << it.first << ": " << it.second << "</li>" << endl;
        }
        os << "</ul>";

        os << "<table>";
        tableEntry(os, "ClientAddress:", request.clientAddress().toString());
        tableEntry(os, "Method:", request.getMethod());

        os << "<table>";

        return os;
    }

  //------------------------------------------------------------------------

      UnknownRequestHandler::UnknownRequestHandler()
        : _logger(Poco::Logger::get("UnknownRequestHandler"))
    {
        _logger.setLevel(Poco::Message::PRIO_TRACE);
        //_logger.trace(__PRETTY_FUNCTION__);
    }

    void UnknownRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) {
        NameValueCollection messages;

        bool error(false);
        try {

            if (request.getMethod() == "GET") {
                throw UnexpectedArgumentException("UnknownRequestHandler called with GET method.");
            }

        } catch (OptionException e) {
            _logger.information(e.className());
            _logger.information(e.message());
            error = true;
        } catch (Poco::Exception e) {
            _logger.information(e.className());
            _logger.information(e.message());
            error = true;
        } catch (...) {
            _logger.error("Unknown exception");
            error = true;
        }

        write(request, response);
    }

      void UnknownRequestHandler::write(HTTPServerRequest &request, HTTPServerResponse &response) {
          _logger.trace(__PRETTY_FUNCTION__);

          Page page("Unknown", request, response);
          //auto data = page.setFormData(_formData);
          page.add(new HeaderContent(page));
          page.add(new UnknownContent(page));
          page.add(new FooterContent(page));
          page.send();

      }

} // namespace jcl

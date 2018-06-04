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

#include <Util/HtmlTags.hpp>
#include <JclServer/Page.hpp>
#include <JclServer/HeaderContent.hpp>
#include <JclServer/FooterContent.hpp>
#include <JclServer/TextContent.hpp>

#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/OptionException.h>
#include <Poco/URI.h>
#include <Poco/Path.h>

#include <iostream>

namespace jcl {
  using namespace std;
  using namespace Poco::Net;
  using Poco::Util::OptionException;
  using Poco::Util::MissingArgumentException;
  using Poco::Util::UnexpectedArgumentException;

  using jcl::HtmlTags;
    using Poco::Exception;

    UnknownContent::UnknownContent(Page &page)
            : PageContent("Unknown", page) {
    }

    std::ostream &UnknownContent::write(std::ostream &os) const {
        os << R"msgx(<p>UnknownContent</p>)msgx" << endl;

        auto& request = _page.getRequest();
        HTMLForm form(request, request.stream());

        Poco::URI uri{_page.getRequest().getURI()};
        Poco::Path path{uri.getPath()};
        auto data = _page.getFormData();
        data.set("page.h1", "Unknown Request Handler");

        string req{path.directory(0)};

        // Display request
        os << "<p>URI: "     << uri.toString() << "</p>" << endl;
        os << "<p>path: "    << uri.getPath()  << "</p>" << endl;
        os << "<p>request: " << req            << "</p>" << endl;

        // Display header records
        os << "<p>Header Records:" << "<table>" << endl;
        for (auto it : _page.getRequest()) {
            os << HtmlTags::tableEntry(it) << endl;
        }
        os << "</table></p>" << endl;

        os << "<p>Form:</p>" << endl;
        os << "<table>" << endl;
        os << "<tr><th>size</th><td>" << form.size() << "</td></tr>" << endl;
        for (auto it : form ) {
            os << HtmlTags::tableEntry(it) << endl;
        }
        for (int i = 0; i < form.size(); ++i) {
            //
            // os << HtmlTags::tableEntry()
        }
        os << "</table></p>" << endl;

        NameValueCollection cookies;
        request.getCookies(cookies);
        os << "<p>Cookies:</>" << "<ul>";
        for (auto it : cookies ) {
            os << "<li>" << it.first << ": " << it.second << "</li>" << endl;
        }
        os << "</ul>" << endl;

        os << "<p>FormData" << endl << "<table>" << endl;
        for (auto it : data) {
           os << HtmlTags::tableEntry(it) << endl;
        }
        os << "</table></p>" << endl;

        os << "<table>" << endl;
        os << HtmlTags::tableEntry("ClientAddress:", request.clientAddress().toString());
        os << HtmlTags::tableEntry("Method:", request.getMethod());
        os << "</table>";

        return os;
    }

  //------------------------------------------------------------------------

      UnknownRequestHandler::UnknownRequestHandler()
        : _logger(Poco::Logger::get("UnknownRequestHandler"))
    {
        _logger.setLevel(Poco::Message::PRIO_TRACE);
        _logger.trace(__PRETTY_FUNCTION__);
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
          auto& data = page.getFormData();

          // Set Page Title
          data.set("page.title", "Unknown Handler");

          // Set Header Content heading
          data.set("page.h1", "Unknown Request Handler");
          data.set("page.h1", "sadness");

          try {
              auto h1 = data.get("page.h1");
          } catch(Exception& e) {
              cerr << "Exception: " << e.message() << endl;
          }

          page.add(new HeaderContent(page));
          page.add(new UnknownContent(page));
          page.add(new FooterContent(page));
          page.send();

      }

} // namespace jcl

// PageContent.cpp
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

#include <JclServer/PageContent.hpp>

#include <JclServer/Page.hpp>

#include <Poco/Util/Application.h>

#include <iostream>

#include <Poco/Exception.h>

namespace jcl {
    using namespace std;
    using namespace Poco;
    using Poco::Net::NameValueCollection;

    PageContent::PageContent(const string &name)
            : _name(name)
            , _logger(Poco::Logger::get("PageContent"))
            , _loggingLevel("none")
    {
        string level = Util::Application::instance().config().getString("application.log_level", "none");
        _logger.setLevel(level);

        _logger.trace(__PRETTY_FUNCTION__ + name);
    }

    PageContent::~PageContent() {
        _logger.trace(__PRETTY_FUNCTION__ + _name);

    }

    void PageContent::setName(const std::string &name) {
        _name = name;
    }

    const string PageContent::getName() const {
        return _name;
    }

    Page &PageContent::getPage() const {
        return *_page;
    }

    void PageContent::setPage(Page* page)
    {
        _page = page;
    }

    Page &PageContent::getPage() {
        return static_cast<const PageContent &>(*this).getPage();
    }

    NameValueCollection &PageContent::getData() const {
        return _page->getFormData();
    }

    NameValueCollection &PageContent::getData() {
        return const_cast<NameValueCollection &>(
                static_cast<const PageContent &>(*this).getData());
    }

    ostream &PageContent::write(ostream &os) const {
        os << "const PageContent" << endl;
        return os;
    }

    ostream &PageContent::write(ostream &os) {
        os << "PageContent" << endl;
        return static_cast<const PageContent &>(*this).write(os);
    }

    bool PageContent::verify() const {
        return false;
    }

}
    

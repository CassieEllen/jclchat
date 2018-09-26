// PageContent.hpp
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

#ifndef PageContent_INCLUDED
#define PageContent_INCLUDED

#include <JclServer/PocoClasses.hpp>

#include <Poco/Exception.h>

#include <memory>
#include <string>
#include <vector>

namespace jcl {

    class Page;

    class PageContent
    {
    public:
        /// @brief Disable creation of default constructor
        PageContent() = delete;

        /// @brief Constructor
        ///
        /// @param name Creates a section named <i>jcl::PageContent</i>
        /// @param page A reference to the containing page.
        explicit PageContent(const std::string& name);

        /// @brief Destructor
        //
        // I would use a default destructor, but I want to get a log message when the destructor is called.
        //virtual ~PageContent() = default;
        virtual ~PageContent();

        /// @brief Do not allow copy.
        PageContent(const PageContent&) = delete;

        /// @brief Do not allow copy
        /// @return undefined
        PageContent&operator=(const PageContent&) = delete;

        /// @brief Sets the name of the content object
        /// @param name the new name for this content instance
        void setName(const std::string& name);

        /// @brief Gets the content's name
        /// @return the name
        const std::string getName() const;

        /// @brief Sets the owning page.
        /// @param page shared pointer to the owning page.
        void setPage(Page* page);

        /// @brief Returns a reference to the containing page
        /// @return a reference to the containing page
        Page& getPage() const;

        /// @brief Returns a reference to the containing page
        /// @return a reference to the containing page
        Page& getPage();

        Poco::Net::NameValueCollection& getData() const;
        Poco::Net::NameValueCollection& getData();

        /// @brief Writes out the content
        /// @param os std::ostream to write to
        /// @return the std::ostream
        virtual std::ostream& write(std::ostream& os);

        /// @brief Writes out the content
        /// @param os std::ostream to write to
        /// @return the std::ostream
        virtual std::ostream& write(std::ostream& os) const;

        /// @brief Verifies the data from this content is valid.
        ///
        /// Does a verification of Form data for this content. If the data
        /// is incorrect, it will set variables in the response.
        ///
        /// @return true if the content is okay. False otherwise.
        virtual bool verify() const;

    protected:
        /// @brief The name of this content object.
        std::string _name;

        /// @brief A reference to the containing page.
        mutable Page* _page;

        Poco::Logger& _logger;
        std::string _loggingLevel;
    };

    // ------------------------------------------------------------------------

    /// @brief stream manipulator to write out PageContent
    /// @param os the std::ostream to write content to.
    /// @param rhs The content to write out.
    /// @return the given std::ostream.
    inline std::ostream& operator<<(std::ostream& os, PageContent& rhs)
    {
        return rhs.write(os);
    }

    /// @brief stream manipulator to write out PageContent
    /// @param os the std::ostream to write content to.
    /// @param rhs The content to write out.
    /// @return the given std::ostream.
    inline std::ostream& operator<<(std::ostream& os, const PageContent& rhs)
    {
        return rhs.write(os);
    }

}
#endif // PageContent_INCLUDED

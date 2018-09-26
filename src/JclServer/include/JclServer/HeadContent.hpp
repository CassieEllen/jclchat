/// @file HeadContent.hpp
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

#ifndef HeadContent_INCLUDED
#define HeadContent_INCLUDED

#include <JclServer/PageContent.hpp>

namespace jcl {

    /// @brief Contains the &lt;head> . . . &lt;/head> section
    /// <p>Content for the <head>...</head> section/p>
    /// <p>The page title is set by the key "page.title"</p>
    ///
    class HeadContent : public PageContent
    {
    public:
        /// @brief Constructor
        HeadContent();

        /// @brief Destructor
        virtual ~HeadContent() = default;

        /// @brief Writes the content to ostream
        /// @param os the stream to write to
        /// @return the stream ostream
        std::ostream& write(std::ostream& os) override;

        /// @brief Writes the content to ostream
        /// @param os the stream to write to
        /// @return the stream ostream
        std::ostream& write(std::ostream& os) const override;

    private:


    };

}
#endif // HeadContent_INCLUDED

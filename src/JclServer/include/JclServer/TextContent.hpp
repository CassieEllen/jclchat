// TextContent.hpp
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

#ifndef TextContent_INCLUDED
#define TextContent_INCLUDED

#include <JclServer/PageContent.hpp>


namespace jcl {

    class TextContent : public PageContent {
    public:
        /// @brief Constructor
        /// @param name name of the text content object
        /// @param text text content
        TextContent(const std::string &name, const std::string &text);

        /// @brief Destructor
        virtual ~TextContent();

        /// @brief Writes the contents of this object to the output stream
        /// @param os output stream
        /// @return output stream
        std::ostream &write(std::ostream &os) const override;

        /// @brief Writes the contents of this object to the output stream
        /// @param os output stream
        /// @return output stream
        std::ostream &write(std::ostream &os) override;

        /// @brief Sets the contents of this object
        /// @param text text content
        void setText(const std::string &text);

    private:
        /// @brief Text content of this object
        std::string _text;
    };

}
#endif // TextContent_INCLUDED

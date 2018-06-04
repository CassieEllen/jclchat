// HtmlTags.hpp
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

#ifndef HtmlTags_INCLUDED
#define HtmlTags_INCLUDED

#include <Poco/Net/NameValueCollection.h>

#include <utility>

namespace jcl {

    class HtmlTags
    {
    public:
        /// @brief Implement an HTML input tag
        /// @param values tag attributes
        /// @return The HTML string for an input tag
      static std::string input(Poco::Net::NameValueCollection &values);

        static std::string tableEntry( const std::string &key, const std::string &value );
        static std::string tableEntry( std::pair<std::string, std::string> );
    };

}
#endif // HtmlTags_INCLUDED

          

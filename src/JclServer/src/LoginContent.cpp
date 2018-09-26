// LoginContent.cpp
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
//
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier:	GPL-3.0

#include <JclServer/LoginContent.hpp>
#include <JclServer/HeaderContent.hpp>
#include <JclServer/FooterContent.hpp>

#include <iostream>


namespace jcl {
    using namespace std;

    LoginContent::LoginContent()
        : PageContent("Login")
    {
    }

    std::ostream& LoginContent::write(std::ostream& os) const
    {
        os <<
R"msgx(
<h1>Login</h1>
)msgx"
           << R"msgx(
<form action="/verify" method="post" enctype="text/plain">
<table>
<tr><td>Email:    </td><td><input type="text" name="email" size="16" maxlength="32"></td></tr>
<tr><td>Password: </td><td><input type="text" name="password" size="16" maxlength="32"></td></tr>
<tr><td>          </td><td><input type="submit" name="login" value="Login"></td></tr>
</table>
</form>
)msgx" << endl;

        return os;
    }
}
    

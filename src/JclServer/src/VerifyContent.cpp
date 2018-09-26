// VerifyContent.cpp
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

#include <JclServer/VerifyContent.hpp>

#include <iostream>

namespace jcl {
    using namespace std;

    VerifyContent::VerifyContent()
        : PageContent("Verify")
    {
    }

    std::ostream& VerifyContent::write(std::ostream& os) const
    {
        os << R"msg(
<p>Verify Content</p>
<p>You have been emailed a verify code. Please enter it here</p>
<form action="profile" method="post">
<p><input type="text" name="code" size="6" maxlength="6"><input type="submit" name="check" value="Check"></p>
</form>
<p>Or <a href="verify">Resend</a> the code.</p>
         )msg";
    }
}
    
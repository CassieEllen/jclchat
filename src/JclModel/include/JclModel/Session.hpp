// Session.h
//
// <one line to give the program's name and a brief idea of what it does.>
// Copyright (C) 2017 Cassie E Nicol
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

#ifndef Session_INCLUDED
#define Session_INCLUDED

#include <Poco/DateTime.h>
#include <Poco/AutoPtr.h>
#include <Poco/Crypto/Cipher.h>

namespace jcl {

class Session
{
 public:
    Session();
    ~Session();
    
    std::string encryptString(const std::string& value);
    std::string decryptString(const std::string& value);
  
 private:
    Poco::AutoPtr<Poco::Crypto::Cipher> _pCipher;
    long _sessionId;
    long _userId;
    Poco::DateTime _timestamp;
};
}
#endif // Session_INCLUDED

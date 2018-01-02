// Session.cpp
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

#include <JclModel/Session.hpp>

#include <Poco/Crypto/Cipher.h>
#include <Poco/Crypto/CipherFactory.h>
#include <Poco/Crypto/CipherKey.h>
#include "Poco/String.h"
#include "Poco/StringTokenizer.h"

namespace jcl {
    using namespace std;
    using namespace Poco::Crypto;
    using Poco::Crypto::CipherFactory;

    Session::Session()
    {
        CipherFactory& factory = CipherFactory::defaultFactory();
        _pCipher = factory.createCipher(CipherKey("aes-256"));
    }

    Session::~Session()
    {
    }

    string Session::encryptString(const string& value)
    {
        return _pCipher->encryptString(value, Cipher::ENC_BASE64);
    }

    std::string Session::decryptString(const std::string& value)
    {
        return _pCipher->decryptString(value, Cipher::ENC_BASE64);
 
    }

}
    

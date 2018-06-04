// JclRequestHandlerFactory.h
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

#ifndef JclRequestHandlerFactory_h__
#define JclRequestHandlerFactory_h__

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <JclServer/PocoClasses.hpp>

namespace jcl {

    class JclPageRequestHandler;
    class Model;

    enum class RequestType {
        rtUnknown,
        rtIndex,
        rtLogin,
        rtFile,
        rtRegister,
        rtVerify
    };

    ///
    /// Provides a factory for request handlers.
    ///
    class JclRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
    {
    public:
        /// ctor
        explicit JclRequestHandlerFactory(jcl::Model& model);

        virtual Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

    private:
        Poco::Net::HTTPRequestHandler* getActionHandler(const Poco::Net::HTTPServerRequest& request,
                                                        RequestType action) const;

        std::string getSessionId(const Poco::Net::HTTPServerRequest& request);
        void removeSession(const Poco::Net::HTTPServerRequest& request);
        RequestType getAction(const Poco::Net::HTTPServerRequest& request) const;

        jcl::Model& _model;
        Poco::Logger& _logger;
    };


}

#endif // JclRequestHandlerFactory_h__

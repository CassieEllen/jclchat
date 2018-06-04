// JclRequestHandlerFactory

#include <JclServer/JclRequestHandlerFactory.hpp>

#include <JclServer/JclRequestHandler.hpp>

#include <JclServer/FileRequestHandler.hpp>
#include <JclServer/LoginRequestHandler.hpp>
#include <JclServer/RegisterRequestHandler.hpp>
#include <JclServer/UnknownRequestHandler.hpp>
#include <JclServer/VerifyRequestHandler.hpp>
#include <JclServer/WelcomeRequestHandler.hpp>

#include <Util/Util.h>

#include <JclModel/Model.hpp>

#if 0
#include <HtmlPages/WelcomeHandler.h>
#include <HtmlPages/UnknownHandler.h>
#include <HtmlPages/VerifyHandler.h>
#endif

#include <iostream>
#include <memory>
#include <regex>
#include <sstream>

#include <boost/filesystem.hpp>

#include "Poco/URI.h"

#include <Poco/Logger.h>
#include "Poco/Net/HTMLForm.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>

#include "Poco/MD5Engine.h"

namespace jcl {

    using namespace Poco::Net;
    using namespace std;
    using namespace boost::filesystem;

    JclRequestHandlerFactory::JclRequestHandlerFactory(jcl::Model& model)
            : _model(model)
        , _logger(Poco::Logger::get("Page"))
    {
        _logger.trace(__PRETTY_FUNCTION__);
        _logger.setLevel("trace");
    }

    RequestType JclRequestHandlerFactory::getAction(const HTTPServerRequest& request) const {
        Poco::URI uri{request.getURI()};
        path path(uri.getPath());
        const string &req{ path.string() };

        _logger.information("URI: " + uri.toString());
        _logger.information("path: " + uri.getPath());
        _logger.information("request: " + req);

        if ( req == "/" ) {
            return RequestType::rtIndex;
        }

        static std::regex extPattern(R"msg(.+\.([a-z]+))msg");
        smatch sm;
        bool extFound = regex_match(path.string(), sm, extPattern);
        string extension;
        if(extFound && (2 == sm.size())) {
            _logger.information(path.string());
            ostringstream oss;
            oss << sm.size() << " matches found";
            _logger.information(oss.str());
            for( const auto & it : sm) {
                _logger.information(it);
            }
            extension = sm[1];
            _logger.information("extension: " + extension);
            set<string> fileExtensions {"css", "js", "ico"};
            if (fileExtensions.count(extension)) {
                return RequestType::rtFile;
            }
        }
        return RequestType::rtUnknown;


        if (req == "login") {
            return RequestType::rtLogin;
        }
        if (req == "register") {
            return RequestType::rtRegister;
        }
        if (req == "verify") {
            return RequestType::rtVerify;
        }

        return RequestType::rtUnknown;
    }

    HTTPRequestHandler* JclRequestHandlerFactory::getActionHandler(const HTTPServerRequest& request, RequestType action) const
    {
        switch(action) {
            case RequestType::rtIndex:
                return new WelcomeRequestHandler;
            case RequestType::rtLogin:
                return new LoginRequestHandler();
            case RequestType::rtFile:
                return new FileRequestHandler;
            case RequestType::rtRegister:
                return new RegisterRequestHandler;
            case RequestType::rtVerify:
                return new VerifyRequestHandler;
            case RequestType::rtUnknown:
            default:
                return new UnknownRequestHandler;
        }

#if 0
        if( request.getMethod() == "GET") {
            return new UnknownHandler();
        }
        if( action == "verify" ) {
            return new VerifyHandler();
        }
        if( action == "welcome" ) {
            return new WelcomeHandler();
        }
#endif

        return new JclRequestHandler();
    }

    /*
    method: GET
        Host: localhost:9090
        User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:57.0) Gecko/20100101 Firefox/57.0

        Accept-Language: en-US,en;q=0.5
        Accept-Encoding: gzip, deflate
        Referer: http://localhost:9090/
        Connection: keep-alive
        Upgrade-Insecure-Requests: 1
    */

    HTTPRequestHandler* JclRequestHandlerFactory::createRequestHandler(const HTTPServerRequest& request)
    {
        _logger.trace(__PRETTY_FUNCTION__);
        _logger.information("--------------------------------------------------");
        _logger.information("--------------------------------------------------");

        // Display header records
        _logger.information("Header Records:");
        for(auto it : request) {
            _logger.information("\t" + it.first + ": " + it.second);
        }

        _logger.information("\tmethod: " + request.getMethod() );

        auto action = getAction(request);
        return getActionHandler(request, action);
    }

    string JclRequestHandlerFactory::getSessionId(const HTTPServerRequest& request)
    {
        NameValueCollection cookies;
        request.getCookies( cookies );

    }

    void JclRequestHandlerFactory::removeSession(const HTTPServerRequest& request)
    {
        NameValueCollection cookies;
        request.getCookies(cookies);
        if( cookies.has("session") ) {
            cout << "Delete session" << endl;
            // Delete session
            auto id = cookies.get("session");
            //Session.delete(id);
        }
    }


}

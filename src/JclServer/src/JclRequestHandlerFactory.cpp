// JclRequestHandlerFactory

#include <JclServer/JclRequestHandlerFactory.hpp>

#include <JclServer/JclRequestHandler.hpp>

#include <JclServer/FileRequestHandler.hpp>
#include <JclServer/LoginRequestHandler.hpp>

#include <Util/Util.h>

#include <JclModel/Model.hpp>

//#include <HtmlPages/IndexHandler.h>
#include <HtmlPages/RegisterHandler.h>
#include <HtmlPages/WelcomeHandler.h>
#include <HtmlPages/UnknownHandler.h>
#include <HtmlPages/VerifyHandler.h>

#include <iostream>
#include <memory>
#include <regex>

#include "Poco/URI.h"
#include "Poco/Path.h"

#include "Poco/Net/HTMLForm.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>

#include "Poco/MD5Engine.h"

using namespace Poco::Net;
using namespace std;


namespace jcl {

    JclRequestHandlerFactory::JclRequestHandlerFactory(jcl::Model& model)
            : _model(model)
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }

    RequestType JclRequestHandlerFactory::getAction(const HTTPServerRequest& request) const
    {
        cout << __PRETTY_FUNCTION__ << endl;

        Poco::URI uri {request.getURI()};
        Poco::Path path {uri.getPath()};
        string req {path.directory(0)};

        cout << "URI: " << uri.toString() << endl;
        cout << "path: " << uri.getPath() << endl;
        cout << "request: " << req << endl;

        std::regex iconPattern(".*\\.ico$");

        bool icon = regex_match(path.toString(), iconPattern);
        RequestType action = RequestType::file;

        cout << "Returning default action login" << endl;
        return RequestType::login;
    }

    HTTPRequestHandler* JclRequestHandlerFactory::getActionHandler(const HTTPServerRequest& request, RequestType action) const
    {
        cout << __PRETTY_FUNCTION__ << endl;

        switch(action) {
        case RequestType::login:
            return new LoginRequestHandler();
            break;
        case RequestType::file:
            return new FileRequestHandler;
            break;
        unknown:
            break;
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


        //return new UnknownHandler();
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
        cout << "\n--------------------------------------------------" << endl;
        cout << __PRETTY_FUNCTION__ << endl;

        Poco::URI uri {request.getURI()};
        cout << "URI: " << uri.toString() << endl;
        cout << "path: " << uri.getPath() << endl;

        // Display header records
        for(auto it : request) {
            cout << "\t" << it.first << ": " << it.second << endl;
        }

        cout << "method: " << request.getMethod() << endl;

        Poco::Path path {uri.getPath()};
        cout << "Path: " << path.toString() << endl;
        cout << "depth: " << path.depth() << endl;
        cout << "directory: " << path.directory(0) << endl;

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

// JclRequestHandlerFactory

#include <JclServer/JclRequestHandlerFactory.hpp>

//#include <JclServer/LoginAction.hpp>
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
    }
    
    HTTPRequestHandler* JclRequestHandlerFactory::getActionHandler(const HTTPServerRequest& request, const string & action)
    {
        cout << __PRETTY_FUNCTION__ << endl;
        
        if( action == "login") {
            //auto p = new LoginAction(_model);
            //shared_ptr<LoginAction> action( p );
            //return action->createRequestHandler(request);
            cout << "returning LoginRequestHandler" << endl;
            return new LoginRequestHandler();
        }
        
        if( request.getMethod() == "GET") {
            return new UnknownHandler();
        }
        if( action == "verify" ) {
            return new VerifyHandler();
        }
        if( action == "welcome" ) {
            return new WelcomeHandler();
        }
        
        
            
        return new UnknownHandler();
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

        string action {path.directory(0)};
        cout << "action: " << action << endl;

        //HTMLForm form(request, request.stream() );

        if( action.empty() ) {
            action = "login";
        }
        cout << "action: " << action << endl;

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

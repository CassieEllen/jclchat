// JclRequestHandlerFactory

#include <JclServer/JclRequestHandlerFactory.hpp>

#include <JclServer/LoginAction.hpp>

#include <Util/Util.h>

#include <JclModel/Model.hpp>

//#include <HtmlPages/IndexHandler.h>
#include <HtmlPages/RegisterHandler.h>
#include <HtmlPages/WelcomeHandler.h>
#include <HtmlPages/UnknownHandler.h>

#include <iostream>

#include "Poco/URI.h"
#include "Poco/Path.h"

#include "Poco/MD5Engine.h"

//Poco::MD5Engine

using namespace Poco::Net;
using namespace std;


namespace jcl {

    JclRequestHandlerFactory::JclRequestHandlerFactory(jcl::Model& model)
            : _model(model)
    {
    }
    
    JclPageRequestHandler* JclRequestHandlerFactory::getActionHandler(const HTTPServerRequest& request, const string & action)
    {
        if( action == "login") {
            auto action = LoginAction(request, _model);
            return action.createRequestHandler(request);
        }
        
        if( request.getMethod() == "GET") {
            return new UnknownHandler();
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
        
        if( action.empty() ) {
            action = "login";
        }

        return getActionHandler(request, action);

#if 0  
            cout << "using IndexHandler" << endl;
            return new IndexHandler();
        } else {
            return getActionHandler(request, action);
        }
        return new JclRequestHandler;
#endif
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

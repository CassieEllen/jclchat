// JclPageRequestHandler.cpp 

#include <HtmlPages/JclPageRequestHandler.h>

#include <JclModel/Model.h>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/NameValueCollection.h>

// For MD5 
#include "Poco/DigestStream.h"
#include "Poco/MD5Engine.h"

// For Session UUID
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"

// For Date & Time
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"

#include <boost/lexical_cast.hpp>

#include <iostream>
#include <sstream>
#include <string>

using Poco::DateTime;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;

using namespace Poco::Net;
using namespace std;


namespace jcl {
    // JclPageRequestHandler::JclPageRequestHandler(Model& model)
    //     : model_(model)
    // {
    //     DateTime now;
    //     dt_ = DateTimeFormatter::format(now, DateTimeFormat::SORTABLE_FORMAT);
    // }

    string JclPageRequestHandler::createSession(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
    {
        using Poco::UUID;
        using Poco::UUIDGenerator;

        UUIDGenerator& generator = UUIDGenerator::defaultGenerator();
        UUID uuid(generator.createRandom());
        string sessionId {uuid.toString()};
        cout << "createSession: " << sessionId << " size: " << sessionId.size() << endl;

        NameValueCollection cookies;
        request.getCookies(cookies);
        cookies.erase("try");
        cookies.erase("session");
        cout << "List:" << endl;
        for(auto item : cookies) {
            cout << "\t" << item.first << ": " << item.second << endl;
        }
        request.setCookies(cookies);
        
        HTTPCookie sessionCookie {"session", sessionId};
        HTTPCookie count {"try", "1"};
        response.addCookie(sessionCookie);
        response.addCookie(count);
        
        return sessionId;
    }
    
    bool JclPageRequestHandler::checkCredentials(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
    {
        
        return true;
    }

    bool JclPageRequestHandler::loggedIn() const
    {
        return false;
    }
    
    string JclPageRequestHandler::encode(const string& val) const
    {
        using Poco::DigestOutputStream;
        using Poco::DigestEngine;
        using Poco::MD5Engine;
        
        MD5Engine md5;
        DigestOutputStream ostr(md5);
        ostr << "This is some text";
        ostr.flush(); // Ensure everything gets passed to the digest engine
        const DigestEngine::Digest& digest = md5.digest(); // obtain result
        std::string result = DigestEngine::digestToHex(digest);
        return result;
    }

    void JclPageRequestHandler::checkCookies(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
    {
        ostringstream oss;
        NameValueCollection cookies;
        request.getCookies(cookies);
        
        oss << "Request Cookies<br>\n";
        for(auto it : cookies ) {
            oss << it.first << ": " << it.second << "<br>\n";
        }
        oss << endl;

        std::vector<HTTPCookie> responseCookies;
        response.getCookies(responseCookies);
        oss << "Response Cookies<br>" << endl;
        for(auto it : responseCookies) {
            oss << it.getName() << ": " << it.getValue() << "<br>" << endl;
        }

        cookieList_ = oss.str();
        cout << cookieList_ << endl;


        request.getCookies(cookies);
        long value = 0;
        if(cookies.has("try")) {
            // Update value
            value = boost::lexical_cast<long>(cookies.get("try"));
            ++ value;
            cout << "Updating try to " << value << endl;
            //response.getCookies(cookies);
            //cookies.set("try", boost::lexical_cast<std::string>(value));
            //response.addCookie( HTTPCookie("try", boost::lexical_cast<std::string>(value)));
        } else {
            // Set value
            cout << "Adding initial cookie try." << endl;
            cookies.add("try", "1");
        }
    }


} // namespace jcl

// JclPageRequestHandler.hpp

#ifndef JclPageRequestHandler_INCLUDED
#define JclPageRequestHandler_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"

#include <JclModel/Model.hpp>

namespace jcl {


    //class JclPageRequestHandler: public Poco::Net::HTTPRequestHandler
class JclPageRequestHandler
{
 public:
    virtual ~JclPageRequestHandler();
    
 public:
    virtual void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) = 0;

 protected:
    void checkCookies(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    bool checkCredentials(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    bool loggedIn() const;
    std::string encode(const std::string& val) const;
    std::string createSession(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

    std::string cookieList_;
    std::string dt_ {};
};


} // namespace jcl


#endif // JclPageRequestHandler_INCLUDED

// JclRequestHandler.h

#ifndef JclRequestHandler_h__
#define JclRequestHandler_h__

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>

#include <Poco/Net/HTTPServerResponse.h>
namespace jcl {

    class JclRequestHandler : public Poco::Net::HTTPRequestHandler
    {
    public:
        virtual void handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp);

    private:
        static int count;
    };
}

#endif // JclRequestHandler_h__

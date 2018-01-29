// JclRequestHandlerFactory.h

#ifndef JclRequestHandlerFactory_h__
#define JclRequestHandlerFactory_h__

#include <Poco/Net/HTTPRequestHandlerFactory.h>
//#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <JclModel/Model.hpp>

namespace Poco {
    namespace Net{
        class HTTPRequestHandler;
        class HTTPServerRequest;
        
    }
}

namespace jcl {

    class JclPageRequestHandler;
    
    class JclRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
    {
    public:
        JclRequestHandlerFactory(jcl::Model& model);
        
        virtual Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

    private:
        Poco::Net::HTTPRequestHandler* getActionHandler(const Poco::Net::HTTPServerRequest& request, const std::string& action);
        
        std::string getSessionId(const Poco::Net::HTTPServerRequest& request);
        void removeSession(const Poco::Net::HTTPServerRequest& request);

        jcl::Model& _model;
    };


}

#endif // JclRequestHandlerFactory_h__

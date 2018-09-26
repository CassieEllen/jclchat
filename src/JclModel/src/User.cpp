
#include <JclModel/User.hpp>

#include <Poco/DigestEngine.h>

#include "Poco/MD5Engine.h"

namespace jcl {
    using namespace std;
    using namespace Poco;

    string digestPassword(const string& password)
    {
        //Poco::MD5Engine engine;
        //engine.update(password);
        //const DigestEngine::Digest& = engine.digest();
        //string digestString(DigestEngine::digestToHex(digest));
        //return digestString;
        return string();
    }
}
    

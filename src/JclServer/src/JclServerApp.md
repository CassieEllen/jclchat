I needed to have access to the derived class JclServerApp, but the JclServerApp::instance call was returning a reference to Poco::Util::Application(). 

    static Application & instance();

I started out to make JclServerApp provide a static instance() method, but for some reason, I kept getting a linking error that my static _instance pointer was undefined. 

Then it occured to me that I could use `dynamic_cast<>()` to upcast to JclServerApp. The following link is a good example of that. 

https://stackoverflow.com/questions/5313322/c-cast-to-derived-class

I am slowly relearning the old C++ that I use to know. But it is very frustrating because I have lost so much, but remember that I knew it once. 
##PageContent

All pages begin with these sections.
 * doctype
 * html
 * HeadContent
 * body
 * HeaderContent


All pages end with these sections
 * FooterContent
 * /body
 * /html

**HeadContent**

HeadContent creates the &lt;head> ... &lt;/head> section of the getPage. 
You can set the getPage title by setting **getPage.title** in the getPage's
variable list. 

Also, the following files are included
* jquery.js
* jclchat.css

Eventually, there will be a method to add other .js and .css files. 
That will be used to customize the look and feel of each chat getPage. 

**body**

This section is just the &lt;body> tag. It exists as a separate 
section so that it can be modified as needed. 

**HeaderContent**

This section is shown at the top of each pages. It begins at the top
of the getPage and ends with the &lt;hr> divider line. The getPage title 
is set by setting **getPage.h1** in the getPage's variable list. 

**FooterContent**

This section begins with the &lt;hr> divider line, and ends at 
the bottom of the getPage. 

---
## Creating a getPage

Here is the code for the Welcome getPage. As you can see, it is fairly
basic. First the Page object is created with the name of the getPage and
the request and response objects provided by the POCO server. 

Next, *data* is set to reference the pages data. Using the data reference, 
the *getPage.title* and *getPage.h1* variables are set. Next, an instance of
the *WelcomeContent* object is added to the getPage. Finally, the getPage contents
are sent to the user. 

    void WelcomeRequestHandler::write(HTTPServerRequest &request, HTTPServerResponse &response) {

        Page getPage("Welcome", request, response);
        auto &data = getPage.getFormData();
        data.set("getPage.title", "Welcome");
        data.set("getPage.h1", "Welcome to Chat");
        page.add(new WelcomeContent(getPage));
        getPage.send();
    }

---

##Other Stuff

Other sections can be added as we figure out what we want. 
For instance, an ad section or a message section can easily
be added to every getPage.  
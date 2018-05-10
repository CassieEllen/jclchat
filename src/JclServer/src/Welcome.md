Welcome Page

Component Sent (Classes)
- HeadContent
- HeaderContent
- WelcomeContent
- FooterContent

Files Involved
- HeadContent.cpp
- HeaderContent.cpp
- WelcomeRequestHandler.cpp
- FooterContent.cpp

As you can see, there are common components that will be used throughout all the pages. Pages begin with HeadContent which is what goes into the &lt;head&gt; section. The &lt;body&gt; section begins with HeaderContent and ends with FooterContent. What goes inbetween is specific per page. 

You can set variables to affect how the content is displayed. To set the page title, you need to set *page.title* in the Page's **_formData** *NameValueCollection*. Here is how it is done in *WelcomeRequestHandler*.

    auto& data = page.getFormData();
    data.set("page.title", "Welcome");
    
Eventually, there will be other special name/value pairs to control the display of the content classes. 

To add other content, look at the preprocessor commented out sections.

Finally, content classes can be created as needed, so the Welcome page an other pages can be as complex as needed.

 
# jclchat POCO based chat program

### To Build

```
 mkdir build
 cd build
 cmake ../src
 make
 alias go='JclChat/JclChat'
 go
```

**The executable is**
 
build/JclChat/JclChat
 
valgrind --tool=memcheck --leak-check=yes JclChat/JclChat


-------------------------------------------------------------------------------

JclChat --daemon --pidfile=/home/cenicol/chat/chat.pid

I have not yet figured out how I want to handle javascript scripts. Right now,
I'm allowing the web server running on the same machine to serve them. I will
probably do that for most static files. 

---

### jclchat.ini
When the chat server starts, it reads from a file called *jclchat.ini*. 

Here is my basic file
```
[Application]
    logger = jclchat

[MySql]
    host = localhost
    port = 3306
    database = jcl
    user = jcl
    password = Secr3t
    compress = true
    auto-reconnect = true

[web]
    host = jclchat.com
    port = 9090
    base = /home/cenicol/CLionProjects/jclchat/src
```
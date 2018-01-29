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

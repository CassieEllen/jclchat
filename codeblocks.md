https://stackoverflow.com/questions/29399512/cmake-codeblocks-hello-world-basic-example

`-G <generator-name>`

  CodeBlocks - Ninja           = Generates CodeBlocks project files.
  CodeBlocks - Unix Makefiles  = Generates CodeBlocks project files.
  
I could not get the "CodeBlocks - Ninja" generator working, but the other works just fine. I kind of am bouncing back and forth between using emacs/cmake/make and codeblocks. Especially since the latter tends to just die at times w/o any indication why. 

Creates a codeblocks project file
```bash
  cd build
  cmake -G "CodeBlocks - Unix Makefiles" ../src
  codeblocks jclchat.cbp &
```

Creates a backup of the entire project, excluding the build directory.

  tar -czv --exclude='*/build/*' -f chat.tgz jclchat


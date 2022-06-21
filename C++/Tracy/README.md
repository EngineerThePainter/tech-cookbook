# Tracy Setup

If you are going to read this, then it means you are a weakling - Tracy has a super-nice manual that covers all features of this tool.

The code here should be used as a reminder for myself how to use the Tracy.

Tracy is an advanced tool for profiling C++ code together with other languages (like Lua). Thanks to it we can trace for example how much time our app
spend in particular functions or we can send some messages that should allow us for better thread understanding.

The recommended way is to include the repository as a third party for your project (once again please read the documentation). 
Then in the Cmake you should enable Tracy as a CMake option and add the `TracyClient.cpp` explicitly to your app.

Then you should build the profiler or capture tools (READ THE DOCUMENTATION IF YOU STILL DIDN'T DO THAT here is the [link](https://github.com/wolfpld/tracy)). I was able to do it on Windows, so you will handle it as well.
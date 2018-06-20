
# Table of contents

* [Overview](#overview)
* [Steps](#steps)
    * [3.1. HTTP client](#http)
* [Result](#result)

TODO:

Application+frame+Reporting
Application+CameraManipulator                        
Application+Debugging                                
Application+DebugCamera                              
Reporter+Stub 
Example+Debugging                                    
Example+DebugApplication                             
Example+HTTPClient  

HTTPClient

* Mongoose
* FetchAPI

Debug

* PageDesc
* Page
* Debugger
* JSON nlohmann's


<a name="overview"/>

# Overview

This example is part of [OpenSceneGraph cross-platform examples][osgcpe].

In this example we implement [debug-broker][debug-broker]'s protocol to support remote
debugging across platforms.

<a name="steps"/>

# Steps

<a name="http"/>

## 3.1. HTTP client

Remote debugging assumes application and debug UI are located at different
machines. The most widespread way to communicate between remote machines
nowadays is to use HTTP(s) over TCP/IP.

We use the following technologies to have HTTP(s) support across platforms:

* [FetchAPI][fetch-api] is [Emscripten][emscripten]'s way to make us of [XHR][xhr]
* [Mongoose][mongoose] is used for desktop and mobile due to intergration simplicity and TLS support

<a name="http-fetch-api"/>

### FetchAPI HTTP client implementation

<a name="http-mongoose"/>

### Mongoose HTTP client implementation

<a name="http-cp"/>

### Cross-platform HTTP client implementation

<a name="result"/>

# Result

![Screenshot](shot.png)

Here's a [web build of the example][web-build].

[osgcpe]: https://github.com/OGStudio/openscenegraph-cross-platform-examples
[debug-broker]: https://github.com/OGStudio/debug-broker
[fetch-api]: https://kripken.github.io/emscripten-site/docs/api_reference/fetch.html
[emscripten]: http://emscripten.org
[xhr]: https://en.wikipedia.org/wiki/XMLHttpRequest
[mongoose]: https://github.com/cesanta/mongoose

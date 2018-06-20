
# Table of contents

* [Overview](#overview)
* [Steps](#steps)
    * [3.1. HTTP(s) support](#http)
        * [Technologies](#http-tech)
        * [Internal representation](#http-representation)
        * [Usage](#http-usage)
* [Result](#result)

TODO:

Application+frame+Reporting
Application+CameraManipulator                        
Application+Debugging                                
Application+DebugCamera                              
Reporter+Stub 
Example+Debugging                                    
Example+DebugApplication                             


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

## 3.1. HTTP(s) support

Remote debugging assumes application and debug UI are located at different
machines. The most widespread way to communicate between remote machines
nowadays is to use HTTP(s) over TCP/IP.

<a name="http-tech"/>

### Technologies

We use the following technologies to have HTTP(s) support across platforms:

* [Fetch API][fetch-api]
    * is only used under web
    * is [Emscripten][emscripten]'s way to make us of [XHR][xhr]
* [Mongoose][mongoose]
    * is used under desktop and mobile
    * is easy to integrate and supports TLS

<a name="http-representation"/>

### Internal representation

These technologies are mapped to the following classes:

* [HTTPClientFetch][src-HTTPClientFetch]
    * supports only single request per instance
    * currently only handles responses up to 1024 characters
* [HTTPClientMongoose][src-HTTPClientMongoose]
    * supports only single request per instance
    * requires client code to call its `process()` function regularly to process the request
* [HTTPClient][src-HTTPClient]
    * supports any number of requests per instance by creating and destroying as many `HTTPClientFetch`/`HTTPClientMongoose` instances as necessary
    * requires client code to call its `process()` function regularly to process requests

<a name="http-usage"/>

### Usage

Client code should:

* create `HTTPClient` instance ([complete version][src-HTTPClient-create]):

    ```
    this->httpClient = new network::HTTPClient;
    ```
* regularly call its `process()` function ([complete version][src-HTTPClient-process]):
    ```
    if (this->httpClient->needsProcessing())
    {
        this->httpClient->process();
    }
    ```
* make requests when necessary
    * in this example only [Debugger][src-Debugger] does requests


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

[src-HTTPClientFetch]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/web/src/network.h#L48
[src-HTTPClientMongoose]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/network.h#L38
[src-HTTPClient]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/network.h#L145
[src-Debugger]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/debug.h#L246
[src-HTTPClient-create]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/Example.h#L130
[src-HTTPClient-process]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/Example.h#L132

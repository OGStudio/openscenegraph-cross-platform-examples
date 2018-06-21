
# Table of contents

* [Overview](#overview)
* [Steps](#steps)
    * [3.1. Introduce HTTP(s) client](#http)
        * [3.1.1. Technologies](#http-tech)
        * [3.1.2. Internal representation](#http-representation)
        * [3.1.3. Usage](#http-usage)
    * [3.2. Introduce debugging support](#debug)
        * [3.2.1. Technologies](#debug-tech)
        * [3.2.2. Internal representation](#debug-representation)
        * [3.2.3. Usage](#debug-usage)
* [Result](#result)

<a name="overview"/>

# Overview

This example is part of [OpenSceneGraph cross-platform examples][osgcpe].

In this example we implement [debug-broker][debug-broker]'s protocol to support remote
debugging across platforms.

<a name="steps"/>

# Steps

<a name="http"/>

## 3.1. Introduce HTTP(s) client

Remote debugging assumes application and debug UI are located at different
machines. The most widespread way to communicate between remote machines
nowadays is to use HTTP(s) over TCP/IP.

<a name="http-tech"/>

### 3.1.1. Technologies

We use the following technologies to have HTTP(s) support across platforms:

* [Fetch API][fetch-api]
    * is only used under web
    * is [Emscripten][emscripten]'s way to make us of [XHR][xhr]
* [Mongoose][mongoose]
    * is used under desktop and mobile
    * is easy to integrate and supports TLS

<a name="http-representation"/>

### 3.1.2. Internal representation

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

### 3.1.3. Usage

Client code:

* creates `HTTPClient` instance ([complete version][src-HTTPClient-create]):
    ```
    this->httpClient = new network::HTTPClient;
    ```
* regularly calls its `process()` function ([complete version][src-HTTPClient-process]):
    ```
    if (this->httpClient->needsProcessing())
    {
        this->httpClient->process();
    }
    ```
* makes HTTP(s) requests when necessary (only [Debugger][src-Debugger] does requests in this examle)

<a name="debug"/>

## 3.2. Introduce debugging support

We use [debug-broker][debug-broker]'s protocol to implement remote debugging.

`debug-broker` is a mediator between debugged application (this example) and
debug UI (source of user input).

<a name="debug-tech"/>

### 3.2.1. Technologies

`debug-broker` has the following concepts:

* Debugger
    * is a container of so-called debug pages
    * usually represents a single application
    * requires client code to call its `process()` function regularly to perform requests when necessary
* Page
    * is a container of so-called debug items
    * usually represents a set of related items, e.g., `Camera` properties
* Item
    * contains alterable entries
    * usually represents properties, e.g., `BackgroundColor` item for `Camera` page
    * can be read-only or read-write

`debug-broker` accepts and replies in JSON format. We use
[NLohmann's JSON][nlohmann-json] to parse incoming JSON. Outgoing JSON
is currently composed manually.

<a name="debug-representation"/>

### 3.2.2. Internal representation

`debug-broker` concepts are mapped to the following classes:

* [Debugger][src-Debugger]
    * is a container for `Page`s
    * uses `HTTPClient` instance to communicate with `debug-broker`
    * makes new request
        * each second
        * only after previous request has been completed
* [Page][src-Page]
    * is a container for `Page::Item`s
* [Page::Item][src-PageItem]
    * is an entry with alterable value

<a name="debug-usage"/>

### 3.2.3. Usage

Client code:

* creates `Debugger` instance ([complete version][src-Debugger-create]):
    ```
    this->dbg = new debug::Debugger(this->httpClient, EXAMPLE_TITLE);
    ```
* provides `debug-broker`'s address ([complete version][src-Debugger-address]):
    ```
    this->dbg->setBrokerURL("http://localhost:7999");
    ```
* regularly calls its `process()` function ([complete version][src-Debugger-process]):
    ```
    this->dbg->process();
    ```

<a name="debug-camera"/>

## 3.3. Debug camera

Now that we covered prerequisites, it's finally time to see how to debug something.

Let's alter camera's background color and also print its current position + rotation.

TODO:

Application+CameraManipulator                        
Application+Debugging                                
Application+DebugCamera                              

Example+Debugging                                    
Example+DebugApplication                             




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
[nlohmann-json]: https://github.com/nlohmann/json

[src-HTTPClientFetch]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/web/src/network.h#L48
[src-HTTPClientMongoose]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/network.h#L38
[src-HTTPClient]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/network.h#L145
[src-Debugger]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/debug.h#L246
[src-HTTPClient-create]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/Example.h#L130
[src-HTTPClient-process]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/Example.h#L132

[src-Debugger]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/debug.h#L246
[src-Page]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/debug.h#L99
[src-PageItem]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/debug.h#L114
[src-Debugger-create]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/Example.h#L157
[src-Debugger-address]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/Example.h#L159
[src-Debugger-process]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/03.RemoteDebugging/desktop/src/Example.h#L164

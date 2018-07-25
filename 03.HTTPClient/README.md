
# Table of contents

* [Overview](#overview)
* [Steps](#steps)
    * [2.1. Implement HTTPClient as a host-guest entity](#hostguest)
        * [Desktop](#desktop)
        * [iOS](#ios)
        * [Android](#android)
        * [Web](#web)
    * 2.2. Regularly poll passive HTTPClient for it to recycle used requests.
    * TODO

* [Result](#result)

TODO explain features:

* Application+camera
* Application+frame+Reporting
* Application+HTTPClient
* Application+HTTPClientProcessor
* Reporter+Stub
* Example+HTTPSGetPost
* HTTPClient
* HTTPRequest

* HTTPClientProcessor (desktop + web)

* HTTPRequestProcessorMongoose (desktop)
* extlib-mongoose (desktop)

* HTTPRequestProcessorFetch (web)
* extlib-fetch (web)

Android C++:
* library+httpClient-android
* library+jniStrings-android

Android Java:
* library+httpClient
* HTTPClientProcessor
* HTTPRequest
* HTTPRequestDelegate
* MainActivity+HTTPClientProcessor

iOS C++:
* library+httpClient-ios

iOS Objective-C:
* AppDelegate+HTTPClientProcessor
* HTTPClientProcessor

<a name="overview"/>

# Overview

This example is part of [OpenSceneGraph cross-platform examples][osgcpe].

In this example we implement HTTP (with TLS support) client across platforms
to perform GET/POST requests.

**Note**: this example builds on the [previous one][ex-prev], make sure to study it.

<a name="steps"/>

# Steps

<a name="hostguest"/>

## 2.1. Implement HTTPClient as a host-guest entity

Each platform (deskop, android, ios, web) has its own stack of technlogies
to perform HTTP(s) requests. Desktop and web have these technologies fully
represented by C++ libraries. However, Android and iOS have these technologies
in different languages: Java and Objective-C correspondingly.

In order to have a unified implementation across platforms, we need to
think of HTTPClient as a host-guest entity. This means that C++ code,
which is exactly the same across platforms, to serve as guest is passive:
it serves as a container for host to take requests from, execute them,
and then pass results back to the guest.


<a name="result"/>

# Result

![Screenshot](shot.png)

Here's a [web build of the example][web-build].

[osgcpe]: https://github.com/OGStudio/openscenegraph-cross-platform-examples
[ex-prev]: ../02.TextureImage


[web-build]: https://ogstudio.github.io/openscenegraph-cross-platform-examples-web-builds/examples/03/ex03-http-client.html


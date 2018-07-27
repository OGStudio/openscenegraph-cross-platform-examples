
# Table of contents

* [Overview](#overview)
* [Architecture](#architecture)
* [Steps](#steps)
    * [2.1. Implement guest side classes](#guest)
    * [2.2. Implement HTTPClientProcessor for desktop and web hosts](#http-client-processor)
    * [2.3. Implement HTTPRequestProcessorMongoose for desktop host](#http-request-processor-mongoose)
    * [2.4. Implement HTTPRequestProcessorFetch for web host](#http-request-processor-fetch)
    * [2.5. Implement HTTP support for Android](#android)
        * [Java side](#android-java)
        * [C++ side](#android-cpp)
    * [2.6. Implement HTTP support for iOS](#ios)
        * [Objective-C side](#ios-objc)
        * [C++ side](#ios-cpp)

* [Result](#result)

TODO explain features:

iOS C++:
* library+httpClient-ios

iOS Objective-C:
* AppDelegate+HTTPClientProcessor
* HTTPClientProcessor

<a name="overview"/>

# Overview

This example is part of [OpenSceneGraph cross-platform examples][osgcpe].

In this example we implement HTTP client (with TLS support) working across
platforms to perform GET/POST requests.

**TODO**: rephrase article dependencies just like in OSGCPG.

**Note**: this example builds on the [previous one][ex-prev], make sure to study it.

<a name="architecture"/>

# Architecture

Each platform has its own stack of technologies to perform HTTP(s) requests:

* Desktop can utilize almost any library (we use [Mongoose][mongoose] with [OpenSSL][openssl])
* Web (Emscripten) provides [Fetch API][FetchAPI]
* Android provides [HttpURLConnection][HttpURLConnection] in Java
* iOS provides [NSURLSession][NSURLSession] in Objective-C

Such a variaty of platform specific technologies is best addressed by
implementing host-guest relationship:

* guest (platform agnostic)
    * provides networking representation
    * used by cross-platform C++ code
* host (specific platform)
    * polls guest for pending requests
    * processes them
    * reports results back to the guest

<a name="steps"/>

# Steps

<a name="guest"/>

## 2.1. Implement guest side classes

Guest side contains the following classes:

* [HTTPClient][HTTPClient]
    * provides `get(...)` function to perform HTTP(s) GET request
    * provides `post(...)` function to perform HTTP(s) POST request
    * creates new `HTTPRequest` instance for each request
* [HTTPRequest][HTTPRequest]
    * contains URL
    * contains payload
        * if payload is empty, hosts perform GET request
        * if payload is non-empty, hosts perform POST request
    * contains success and failure callbacks

Cross-platform client code uses `HTTPClient` exclusively to perform HTTP(s) requests.

<a name="http-client-processor"/>

## 2.2. Implement HTTPClientProcessor for desktop and web hosts

Both desktop and web use [HTTPClientProcessor][HTTPClientProcessor]:

* processes single `HTTPClient` instance
* is [regularly called][HTTPClientProcessor-processing] by `Application` to process requests
* creates either `HTTPRequestProcessorMongoose`, or `HTTPRequestProcessorFetch` instance for each `HTTPRequest` instance

<a name="http-request-processor-mongoose"/>

## 2.3. Implement HTTPRequestProcessorMongoose for desktop host

We prefer [Mongoose][mongoose] to other options because it's
easy to use and integrate.

[HTTPRequestProcessorMongoose][HTTPRequestProcessorMongoose]:

* uses `Mongoose`
* manages single `HTTPRequest` instance

To support requests to HTTPS, make sure to:

* [enable OpenSSL support in Mongoose][mongoose-openssl]
* [link with OpenSSL libraries][link-openssl]

<a name="http-request-processor-fetch"/>

## 2.4. Implement HTTPRequestProcessorFetch for web host

[Fetch API][FetchAPI] is the recommended way for Emscripten web applications
to issue `XMLHttpRequest`s to perform HTTP(s) requests.

[HTTPRequestProcessorFetch][HTTPRequestProcessorFetch]:

* uses `Fetch API`
* manages single `HTTPRequest` instance

<a name="android"/>

## 2.5. Implement HTTP support for Android

Android uses Java, so we need to implement HTTP processing at both
Java (host requirement) and C++ (guest requirement) sides.

<a name="android-java"/>

### Java side

Introduce the following classes to Java:

* [HTTPClientProcessor][android-HTTPClientProcessor]
    * is [regularly called][android-HTTPClientProcessor-processing] by `MainActivity`
    * implements `HTTPRequestDelegate` to receive results
    * [polls C++ side][android-library-httpClient-poll] for pending HTTP requests
    * [executes requests][android-HTTPClientProcessor-exec] with the help of `HTTPRequest`
    * [reports results back][android-HTTPClientProcessor-report] to C++ side
* [HTTPRequest][android-HTTPRequest]
    * is an `AsyncTask` that uses `HttpURLConnection` to perform HTTP(s) requests
    * reports results to `HTTPRequestDelegate` instance
* [HTTPRequestDelegate][android-HTTPRequestDelegate]
    * is an interface to delegate `HTTPRequest` results

**Note**: make sure to [add Internet permission][android-manifest-internet] to `AndroidManifest.xml` for
HTTP(s) requests to work.

<a name="android-cpp"/>

### C++ side

Introduce the following native library functions at C++ side:

* [httpClientExecuteNextRequest][android-httpClientExecuteNextRequest]
    * gets next pending request from `HTTPClient`
    * sets its status to `PENDING`
    * decomposes `HTTPRequest` into strings
    * returns these strings to Java side
* [httpClientCompleteRequest][android-httpClientCompleteRequest]
    * composes `HTTPRequest` from strings
    * sets its status to `COMPLETED`

<a name="ios"/>

## 2.6. Implement HTTP support for iOS

Android uses Java, so we need to implement HTTP processing at both
Java (host requirement) and C++ (guest requirement) sides.

<a name="ios-objc"/>

### Objective-C side

<a name="ios-cpp"/>

### C++ side




## 2.?. Change background (camera) color when GET/POST responses arrive

Specific example:
* Application+HTTPClient
* Application+camera
* Example+HTTPSGetPost

Client code uses `HTTPClient` exclusively to perform HTTP(s) requests
([source code][https-get-post]):

```
// Reset background color.
this->app->camera()->setClearColor({ 0, 0, 0, 0 });
// Set background color 50% greener on success.
auto success = [&](std::string response) {
    auto color = this->app->camera()->getClearColor();
    color.y() += 0.5;
    this->app->camera()->setClearColor(color);
    OSGCPE_EXAMPLE_LOG(response.c_str());
};
// Set background color 50% redder on failure.
auto failure = [&](std::string reason) {
    auto color = this->app->camera()->getClearColor();
    color.x() += 0.5;
    this->app->camera()->setClearColor(color);
    OSGCPE_EXAMPLE_LOG(reason.c_str());
};

// GET.
this->app->httpClient->get(
    "https://raw.githubusercontent.com/OGStudio/openscenegraph-cross-platform-examples/master/.gitignore",
    success,
    failure
);

// POST.
this->app->httpClient->post(
    "https://opengamestudio-debug-broker.herokuapp.com",
    "sample-data",
    success,
    failure
);
```

<a name="result"/>

# Result

![Screenshot](shot.png)

Here's a [web build of the example][web-build].

[osgcpe]: https://github.com/OGStudio/openscenegraph-cross-platform-examples
[ex-prev]: ../02.TextureImage

[mongoose]: https://github.com/cesanta/mongoose
[openssl]: https://www.openssl.org
[FetchAPI]: https://kripken.github.io/emscripten-site/docs/api_reference/fetch.html
[HttpURLConnection]: https://developer.android.com/reference/java/net/HttpURLConnection
[NSURLSession]: https://developer.apple.com/documentation/foundation/nsurlsession?language=objc

[HTTPClient]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/desktop/src/network.h#L194
[HTTPRequest]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/desktop/src/network.h#L53
[HTTPClientProcessor]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/desktop/src/network.h#L291
[HTTPClientProcessor-processing]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/desktop/src/Application.h#L159
[mongoose-openssl]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/desktop/src/network-extlib.h#L29
[link-openssl]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/desktop/CMakeLists.txt#L27
[HTTPRequestProcessorMongoose]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/desktop/src/network.h#L89
[HTTPRequestProcessorFetch]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/web/src/network.h#L89

[android-HTTPClientProcessor]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/android/app/src/main/java/MainActivity.java#L588
[android-HTTPClientProcessor-processing]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/android/app/src/main/java/MainActivity.java#L124
[android-library-httpClient-poll]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/android/app/src/main/java/MainActivity.java#L593
[android-HTTPClientProcessor-exec]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/android/app/src/main/java/MainActivity.java#L601
[android-HTTPClientProcessor-report]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/android/app/src/main/java/MainActivity.java#L619
[android-HTTPRequest]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/android/app/src/main/java/MainActivity.java#L498
[android-HTTPRequestDelegate]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/android/app/src/main/java/MainActivity.java#L582
[android-manifest-internet]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/android/app/src/main/AndroidManifest.xml#L6

[android-httpClientExecuteNextRequest]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/android/app/src/main/cpp/library.cpp#L93
[android-httpClientCompleteRequest]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/Mahjong-17/03.HTTPClient/android/app/src/main/cpp/library.cpp#L110

[web-build]: https://ogstudio.github.io/openscenegraph-cross-platform-examples-web-builds/examples/03/ex03-http-client.html


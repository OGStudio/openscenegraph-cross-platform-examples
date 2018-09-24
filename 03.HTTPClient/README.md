
# Table of contents

* [Overview](#overview)
* [Architecture](#architecture)
* [Steps](#steps)
    * [3.1. Implement guest side classes](#guest)
    * [3.2. Implement HTTPClientProcessor for desktop and web hosts](#http-client-processor)
    * [3.3. Implement HTTPRequestProcessorMongoose for desktop host](#http-request-processor-mongoose)
    * [3.4. Implement HTTPRequestProcessorFetch for web host](#http-request-processor-fetch)
    * [3.5. Implement HTTP support for Android](#android)
        * [Java side](#android-java)
        * [C++ side](#android-cpp)
    * [3.6. Implement HTTP support for iOS](#ios)
    * [3.7. Change background (camera) color when GET/POST responses arrive](#change-bg)
* [Result](#result)

<a name="overview"/>

# Overview

This example is part of [OpenSceneGraph cross-platform examples][osgcpe].

In this example we implement HTTP client (with TLS support) working across
platforms to perform GET/POST requests.

**Note**: this example requires [02.TextureImage example][ex02] knowledge.

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

## 3.1. Implement guest side classes

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

## 3.2. Implement HTTPClientProcessor for desktop and web hosts

Both desktop and web use [HTTPClientProcessor][HTTPClientProcessor]:

* processes single `HTTPClient` instance
* is [regularly called][HTTPClientProcessor-processing] by `Application` to process requests
* creates either `HTTPRequestProcessorMongoose`, or `HTTPRequestProcessorFetch` instance for each `HTTPRequest` instance

<a name="http-request-processor-mongoose"/>

## 3.3. Implement HTTPRequestProcessorMongoose for desktop host

We prefer [Mongoose][mongoose] to other options because it's
easy to use and integrate.

[HTTPRequestProcessorMongoose][HTTPRequestProcessorMongoose]:

* uses `Mongoose`
* manages single `HTTPRequest` instance

To support requests to HTTPS, make sure to:

* install OpenSSL development libraries
    * `apt install libssl-dev` under Linux
    * `brew install openssl` under macOS
    * TODO Windows
* [enable OpenSSL support in Mongoose][mongoose-openssl]
* [link with OpenSSL libraries][link-openssl]

**Note**: clone [Mongoose][mongoose] alongside OpenSceneGraph cross-platfrom
examples' repository.

<a name="http-request-processor-fetch"/>

## 3.4. Implement HTTPRequestProcessorFetch for web host

[Fetch API][FetchAPI] is the recommended way for Emscripten web applications
to issue `XMLHttpRequest`s to perform HTTP(s) requests.

[HTTPRequestProcessorFetch][HTTPRequestProcessorFetch]:

* uses `Fetch API`
* manages single `HTTPRequest` instance

**Note**: HTTP(s) requests in web browsers are subject to [Cross-origin resource sharing (CORS)][web-cors],
which means you can't access just any location as free as on desktop or mobile.

<a name="android"/>

## 3.5. Implement HTTP support for Android

Android uses Java, so we need to implement HTTP processing at both
Java (host) and C++ (guest) sides.

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
    * sets the request's status to `IN_PROGRESS`
    * decomposes `HTTPRequest` into strings
    * returns these strings to Java side
* [httpClientCompleteRequest][android-httpClientCompleteRequest]
    * composes `HTTPRequest` from strings
    * sets its status to `COMPLETED`

<a name="ios"/>

## 3.6. Implement HTTP support for iOS

iOS uses Objective-C, so we need to implement HTTP processing at both
Objective-C (host) and C++ (guest) sides.

Introduce [HTTPClientProcessor][ios-HTTPClientProcessor] to Objective-C:

* is [regularly called][ios-HTTPClientProcessor-processing] by `RenderVC`
* [polls C++ side][ios-library-httpClient-poll] for pending HTTP requests
* [executes requests][ios-HTTPClientProcessor-exec] with the help of `NSURLSession`
* [reports results back][ios-HTTPClientProcessor-report] to C++ side

Introduce the following functions to C++:

* [httpClientExecuteNextRequest][ios-httpClientExecuteNextRequest]
    * gets next pending request from `HTTPClient`
    * sets the request's status to `IN_PROGRESS`
    * decomposes `HTTPRequest` details
    * returns decomposed details to Objective-C side
* [httpClientCompleteRequest][ios-httpClientCompleteRequest]
    * composes `HTTPRequest` from details
    * sets its status to `COMPLETED`

**Note**: all HTTP(s) requests in iOS are subject to
[Application Transport Security (ATS)][ios-ats], which means you can access
HTTPS freely, however, domains without TLS must be explicitely whitelisted
in `Info.plist`.

<a name="change-bg"/>

## 3.7. Change background (camera) color when GET/POST responses arrive

With hosts managing `HTTPClient` instance we can finally request some HTTP(s)!

Let's perform GET and POST requests:

* if request succeeds, make green component of background (camera) color 50% lighter
* if request fails, make red component of background (camera) color 50% lighter

Thus:
* if both requests succeed, we should see light green background
* if both requests fail, we should see light red background
* if one request fails and another one suceeds, we should see some other color

Here's how to do it ([source code][https-get-post]):

```
// Reset background color.
this->app->camera()->setClearColor({ 0, 0, 0, 0 });
// Set background color 50% greener on success.
auto success = [&](std::string response) {
    auto color = this->app->camera()->getClearColor();
    color.y() += 0.5;
    this->app->camera()->setClearColor(color);
    OSGCPE_MAIN_EXAMPLE_LOG(response.c_str());
};
// Set background color 50% redder on failure.
auto failure = [&](std::string reason) {
    auto color = this->app->camera()->getClearColor();
    color.x() += 0.5;
    this->app->camera()->setClearColor(color);
    OSGCPE_MAIN_EXAMPLE_LOG(reason.c_str());
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

**Note**: we use specific HTTPS URLs to make sure both [CORS][web-cors] and
[ATS][ios-ats] restrictions are met.

<a name="result"/>

# Result

![Screenshot](shot.png)

Here's a [web build of the example][web-build].

[osgcpe]: https://github.com/OGStudio/openscenegraph-cross-platform-examples
[ex02]: ../02.TextureImage

[mongoose]: https://github.com/cesanta/mongoose
[openssl]: https://www.openssl.org
[FetchAPI]: https://kripken.github.io/emscripten-site/docs/api_reference/fetch.html
[HttpURLConnection]: https://developer.android.com/reference/java/net/HttpURLConnection
[NSURLSession]: https://developer.apple.com/documentation/foundation/nsurlsession?language=objc

[HTTPClient]: desktop/src/network.h#L203
[HTTPRequest]: desktop/src/network.h#L52
[HTTPClientProcessor]: desktop/src/network.h#L300
[HTTPClientProcessor-processing]: desktop/src/main.h#L224

[HTTPRequestProcessorMongoose]: desktop/src/network.h#L88
[mongoose-openssl]: ../libs/mongoose/CMakeLists.txt#L29
[link-openssl]: ../libs/mongoose/CMakeLists.txt#L17

[HTTPRequestProcessorFetch]: web/src/network.h#L88
[web-cors]: https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS

[android-HTTPClientProcessor]: android/app/src/main/java/MainActivity.java#L591
[android-HTTPClientProcessor-processing]: android/app/src/main/java/MainActivity.java#L127
[android-library-httpClient-poll]: android/app/src/main/java/MainActivity.java#L594
[android-HTTPClientProcessor-exec]: android/app/src/main/java/MainActivity.java#L609
[android-HTTPClientProcessor-report]: android/app/src/main/java/MainActivity.java#L619
[android-HTTPRequest]: android/app/src/main/java/MainActivity.java#L501
[android-HTTPRequestDelegate]: android/app/src/main/java/MainActivity.java#L585
[android-manifest-internet]: android/app/src/main/AndroidManifest.xml#L6
[android-httpClientExecuteNextRequest]: android/app/src/main/cpp/library.cpp#L97
[android-httpClientCompleteRequest]: android/app/src/main/cpp/library.cpp#L113

[ios-HTTPClientProcessor]: ios/src/ios.mm#L100
[ios-HTTPClientProcessor-processing]: ios/src/ios.mm#L84
[ios-library-httpClient-poll]: ios/src/ios.mm#L105
[ios-HTTPClientProcessor-exec]: ios/src/ios.mm#L123
[ios-HTTPClientProcessor-report]: ios/src/ios.mm#L135
[ios-httpClientExecuteNextRequest]: ios/src/library.cpp#L66
[ios-httpClientCompleteRequest]: ios/src/library.cpp#L78
[ios-ats]: https://forums.developer.apple.com/thread/6767

[https-get-post]: desktop/src/main.h#L346

[web-build]: https://ogstudio.github.io/openscenegraph-cross-platform-examples-web-builds/examples/03/ex03-http-client.html


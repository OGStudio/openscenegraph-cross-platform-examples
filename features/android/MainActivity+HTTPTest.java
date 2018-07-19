FEATURE MainActivity.java/Setup
this.setupHTTPTest();

FEATURE MainActivity.java/Impl
private void setupHTTPTest()
{
    HTTPRequest request = new HTTPRequest(); 
    request.execute("https://httpbin.org/get");
}

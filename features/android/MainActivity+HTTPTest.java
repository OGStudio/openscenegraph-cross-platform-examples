FEATURE MainActivity.java/Setup
this.setupHTTPTest();

FEATURE MainActivity.java/Impl
void setupHTTPTest()
{
    HTTPRequest request = new HTTPRequest(); 
    request.execute("https://httpbin.org/get");
}

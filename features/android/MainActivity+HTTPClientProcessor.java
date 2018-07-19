FEATURE MainActivity.java/Setup
this.setupHTTPClientProcessor();

FEATURE MainActivity.java/Process
this.httpClientProcessor.process();

FEATURE MainActivity.java/Impl
private HTTPClientProcessor httpClientProcessor = null;
private void setupHTTPClientProcessor()
{
    this.httpClientProcessor = new HTTPClientProcessor();
}

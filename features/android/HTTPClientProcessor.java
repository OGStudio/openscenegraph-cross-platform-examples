FEATURE MainActivity.java/Impl
class HTTPClientProcessor
{
    void process()
    {
        // Collect one pending HTTP request per execution run.
        String[] requestState = library.httpClientExecuteNextRequest();
        String requestString = requestState[0] + "," + requestState[1] + "," + requestState[2];
        Log.e("HTTPClientProcessor", "TODO process request: " + requestString);

        /*
        // Non-empty id means we have request to execute.
        if (id)
        {
            [self
                performHTTPRequestWithId:id
                url:@(url.c_str())
                data:@(data.c_str())
            ]; 
        }
        */
    }
}

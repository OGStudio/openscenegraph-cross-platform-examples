FEATURE MainActivity.java/Include
import android.text.TextUtils;

FEATURE MainActivity.java/Impl
class HTTPClientProcessor
    implements HTTPRequestDelegate
{
    void process()
    {
        // Collect one pending HTTP request per execution run.
        String[] requestParts = library.httpClientExecuteNextRequest();
        // Make sure we have enough request parts to perform actual request.
        if (requestParts.length == 3)
        {
            String id = requestParts[0];
            String url = requestParts[1];
            String data = requestParts[2];
            this.performHTTPRequest(id, url, data);
        }
        // TODO Report failure if number of request parts is different from 3.
    }

    private void performHTTPRequest(String id, String url, String data)
    {
        Log.e("HTTPClientProcessor", "performHTTPRequest. id: " + id + " url: " + url + " data: " + data);
        // NOTE We don't keep a list of requests to prevent GC from collecting
        // NOTE the requests because so far we're fine.
        HTTPRequest request = new HTTPRequest(id, url, data); 
        request.delegate = this;
        request.execute();
    }

    public void completeRequest(String id, boolean status, String response)
    {
        Log.e("HTTPClientProcessor", "Request completed. id: " + id + " status: " + status + " response: " + response);
        library.httpClientCompleteRequest(id, status, response);
    }
}

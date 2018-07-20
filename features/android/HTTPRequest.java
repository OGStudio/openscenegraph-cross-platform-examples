FEATURE MainActivity.java/Include
import android.os.AsyncTask;
// TODO REMOVE
import android.util.Log;
import java.io.InputStream;
import java.io.ByteArrayOutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

FEATURE MainActivity.java/Impl
class HTTPRequest
    extends AsyncTask<Void, Void, String>
{
    private String id;
    private String url;
    private String data;

    HTTPRequestDelegate delegate = null;

    HTTPRequest(String id, String url, String data)
    {
        this.id = id;
        this.url = url;
        this.data = data;
    }
    @Override
    protected String doInBackground(Void... params)
    {
        HttpURLConnection connection = null;
        try
        {
            // Open connection.
            URL address = new URL(this.url);
            connection = (HttpURLConnection)address.openConnection();
            // TODO POST
            // TODO connection.setRequestMethod("GET");
            connection.connect();

            // Get response.
            // Source: https://stackoverflow.com/a/35446009
            InputStream inputStream = connection.getInputStream();
            ByteArrayOutputStream result = new ByteArrayOutputStream();
            byte[] buffer = new byte[1024];
            int length;
            while ((length = inputStream.read(buffer)) != -1)
            {
                result.write(buffer, 0, length);
            }
            String response = result.toString("UTF-8");
            return response;
        }
        catch (Exception e)
        {
            // Report failure.
            if (this.delegate != null)
            {
                this.delegate.completeRequest(id, false, e.getMessage());
            }
            // Report error.
            Log.e("Exception", "Error ", e);
            return null;
        }
        finally
        {
            if (connection != null)
            {
                connection.disconnect();
            }
        }
    }

    @Override
    protected void onPostExecute(String result)
    {
        super.onPostExecute(result);
        // Report success.
        if (this.delegate != null)
        {
            this.delegate.completeRequest(id, true, result);
        }
        Log.e("Response", "result is: " + result);
    }
}

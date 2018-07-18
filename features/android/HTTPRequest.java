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
    extends AsyncTask<String, Void, String>
{
    @Override
    protected String doInBackground(String... params)
    {
        HttpURLConnection connection = null;
        // TODO Do we need to keep this?
        String response = null;

        try
        {
            // Open connection.
            URL url = new URL(params[0]);
            connection = (HttpURLConnection)url.openConnection();
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
            response = result.toString("UTF-8");
            return response;
        }
        /*
        catch (IOException e)
        {
            // TODO Report error.
            Log.e("IOError", "Error ", e);
            return null;
        }
        */
        catch (Exception e)
        {
            // TODO Report error.
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
        Log.e("Response", result);
    }
}

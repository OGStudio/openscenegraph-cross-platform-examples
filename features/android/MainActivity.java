FEATURE MainActivity.java/Include
import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

FEATURE MainActivity.java/Impl
public class MainActivity extends Activity
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}

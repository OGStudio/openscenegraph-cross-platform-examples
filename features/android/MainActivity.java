FEATURE android.java/Include
import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

FEATURE android.java/Impl
public class MainActivity extends Activity
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}

FEATURE MainActivity.java/Include
import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

FEATURE MainActivity.java/Inherit
public class MainActivity
    extends Activity
    implements RendererDelegate

FEATURE MainActivity.java/Setup
{
    private EGLview renderer = null;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        this.setContentView(R.layout.activity_main);
        this.setupRenderer();

FEATURE MainActivity.java/RendererInit
    }
    private void setupRenderer()
    {
        this.renderer = (EGLview)findViewById(R.id.render_surface);
        this.renderer.setDelegate(this);
    }
    public void rendererInit(int width, int height)
    {

FEATURE MainActivity.java/RendererFrame
    }
    public void rendererFrame()
    {

FEATURE MainActivity.java/Impl
    }

FEATURE MainActivity.java/End
}

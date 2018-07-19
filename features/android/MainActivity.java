FEATURE MainActivity.java/Include
import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

FEATURE MainActivity.java/Setup
public class MainActivity extends Activity
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
        InitCallback initCallback = new InitCallback() {
            public void init(int width, int height)
            {
                this.rendererInit(width, height);
            }
        };
        FrameCallback frameCallback = new FrameCallback() {
            public void frame()
            {
                this.rendererFrame();
            }
        };
        this.renderer.setCallbacks(initCallback, frameCallback);
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


package org.opengamestudio.ex04;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

// Input.
import android.view.MotionEvent;
import android.view.View;

public class MainActivity
    extends Activity
    implements View.OnTouchListener
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        this.setContentView(R.layout.activity_main);

        this.setupInput();
    }

    // Input.
    private void setupInput()
    {
        EGLview renderer = (EGLview)findViewById(R.id.render_surface);
        renderer.setOnTouchListener(this);
    }
    @Override
    public boolean onTouch(View view, MotionEvent event)
    {
        int action = event.getAction() & event.ACTION_MASK;
        float x = event.getX(0);
        float y = event.getY(0);
        switch (action)
        {
            /*
            case MotionEvent.ACTION_MOVE:
            {
                player.moveMouse(x, y);
                return true;
            }
            */
            case MotionEvent.ACTION_DOWN:
            {
                library.handleMousePress(true, x, y);
                return true;
            }
            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_CANCEL:
            {
                library.handleMousePress(false, x, y);
                return true;
            }
            default:
                break;
        }
        return false;
    }

}


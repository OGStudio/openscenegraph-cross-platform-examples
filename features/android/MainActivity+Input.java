FEATURE MainActivity.java/Include
import android.view.MotionEvent;
import android.view.View;

FEATURE MainActivity.java/Inherit
, View.OnTouchListener

FEATURE MainActivity.java/Setup
this.setupInput();

FEATURE MainActivity.java/Impl
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

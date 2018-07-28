FEATURE library.cpp/Impl
// Handle mouse press and release events.
OSGCPE_JNI(handleMousePress)(OSGCPE_JNI_ARG, jboolean down, jfloat x, jfloat y)
{
    example->app->handleMousePress(down == JNI_TRUE, x, y);
}

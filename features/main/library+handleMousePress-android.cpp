FEATURE library.cpp/Impl
// Handle mouse press and release events.
JNI_FUNC(handleMousePress)(JNI_ARG, jboolean down, jfloat x, jfloat y)
{
    example->app->handleMousePress(down == JNI_TRUE, x, y);
}

FEATURE library.cpp/Impl
// Setup graphics context.
OSGCPE_JNI(init)(OSGCPE_JNI_ARG, jint width, jint height)
{
    // Create example only once.
    // If we create example at stack, the instance might get initialized
    // before plugin readers/writers are available, which would break everything.
    if (!example)
    {
        example = new osgcpe::Example;
    }
    return example->app->setupWindow(width, height);
}

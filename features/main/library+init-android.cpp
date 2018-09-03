FEATURE library.cpp/Impl
// Setup graphics context.
JNI_FUNC(init)(JNI_ARG, jint width, jint height)
{
    // Create example only once.
    // If we create example at stack, the instance might get initialized
    // before plugin readers/writers are available, which would break everything.
    if (!example)
    {
        main::Example::Parameters parameters;
        example = new main::Example(parameters);
    }
    return example->app->setupWindow(width, height);
}

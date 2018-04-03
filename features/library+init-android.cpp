FEATURE library.cpp/Impl
// Setup graphics context.
OSGCPE_JNI(init)(OSGCPE_JNI_ARG, jint width, jint height)
{
    // Create library application only once.
    // If we create library application at stack, the instance might get initialized
    // before plugin readers/writers are available, which would break everything.
    if (!libapp)
    {
        libapp = new LibraryApplication;
    }
    return libapp->app->setupWindow(width, height);
}

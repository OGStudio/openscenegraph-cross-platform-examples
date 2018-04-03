FEATURE library.h/Decl
// Forward declare UIView for Objective-C++ and C++.
#ifdef __OBJC__
    @class UIView;
#else
    class UIView;
#endif

FEATURE library.h/Impl
// Initialization.
UIView *init(int width, int height, float scale, UIView *parentView);

FEATURE library.cpp/Impl
UIView *init(int width, int height, float scale, UIView *parentView)
{
    // Create library application only once.
    // If we create library application at stack, the instance might get initialized
    // before plugin readers/writers are available, which would break everything.
    if (!libapp)
    {
        libapp = new LibraryApplication;
    }
    return libapp->app->setupWindow(width, height, scale, parentView);
}

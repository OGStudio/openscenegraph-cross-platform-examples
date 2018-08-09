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
    // Create example only once.
    // If we create example at stack, the instance might get initialized
    // before plugin readers/writers are available, which would break everything.
    if (!example)
    {
        main::Example::Parameters parameters;
        example = new main::Example(parameters);
    }
    return example->app->setupWindow(width, height, scale, parentView);
}

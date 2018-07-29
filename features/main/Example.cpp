FEATURE main.h/Setup
struct Example
{
    Application *app;

    Example()
    {
        this->app = new Application(EXAMPLE_TITLE);

FEATURE main.h/TearDown
    }
    ~Example()
    {

FEATURE main.h/Impl
        delete this->app;
    }

FEATURE main.h/End
};

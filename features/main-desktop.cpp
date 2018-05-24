FEATURE main.cpp/Setup
auto example = new osgcpe::Example();
example->app->setupWindow(osgcpe::EXAMPLE_TITLE, 100, 100, 160, 120);

FEATURE main.cpp/Run
example->app->run();
delete example;

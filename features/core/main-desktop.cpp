FEATURE main.cpp/Setup
auto example = new core::Example();
example->app->setupWindow(core::EXAMPLE_TITLE, 100, 100, 480, 320);

FEATURE main.cpp/Run
example->app->run();
delete example;

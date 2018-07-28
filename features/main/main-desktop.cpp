FEATURE main.cpp/Include
#include "main.h"

FEATURE main.cpp/Setup
auto example = new main::Example();
example->app->setupWindow(main::EXAMPLE_TITLE, 100, 100, 480, 320);

FEATURE main.cpp/Run
example->app->run();
delete example;

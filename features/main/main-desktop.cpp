FEATURE main.cpp/Include
#include "main.h"

FEATURE main.cpp/Setup
main::Example::Parameters parameters;

FEATURE main.cpp/End
auto example = new main::Example(parameters);
example->app->setupWindow(main::EXAMPLE_TITLE, 100, 100, 480, 320);

FEATURE main.cpp/Run
example->app->run();
delete example;

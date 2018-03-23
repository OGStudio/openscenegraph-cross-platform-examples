FEATURE main.cpp/Setup
auto app = new osgcpe::Application(appName);
app->setupWindow(appName, 100, 100, 1024, 768);

FEATURE main.cpp/Run
app->run();
delete app;

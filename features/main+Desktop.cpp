FEATURE main.cpp/Setup
auto app = new osgcpe::Application;
app->setupWindow("OSG", 100, 100, 1024, 768);

FEATURE main.cpp/Run
app->run();
delete app;

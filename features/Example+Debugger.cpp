FEATURE Example.h/Instance
osgcpe::Debugger *dbg;

FEATURE Example.h/Setup
// Create debugger.
this->dbg = new osgcpe::Debugger("first");
this->dbg->setConsoleURL("https://remote-debugger.herokuapp.com");
this->setupDebugItems();
// TODO: add debugger to polling or global queue...

FEATURE Example.h/TearDown
delete this->dbg;

FEATURE Example.h/Impl
private:
    void setupDebugItems()
    {
        this->dbg->addItem(
            "LocalTime",
            [this] {
                auto tm = time(0);
                auto now = localtime(&tm);
                return asctime(now);
            }
        );
        this->dbg->addItem(
            "RedBGColor",
            [this] {
                auto color = this->app->bgColor();
                return itoa(color.r * 255.0);
            },
            [this](const std::string &value) {
                auto color = this->app->bgColor();
                color.r = static_cast<float>(atoi(value)) / 255.0;
                this->app->setBGColor(color);
            }
        );
    }


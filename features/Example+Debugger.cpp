FEATURE Example.h/Instance
osgcpe::Debugger *dbg;

FEATURE Example.h/Setup
// Create debugger.
this->dbg = new osgcpe::Debugger;
this->dbg->setConsoleURL("https://remote-debugger.herokuapp.com");
// Create debug groups.
this->setupDebuggerInfo();
this->setupDebuggerBGColor();

FEATURE Example.h/TearDown
delete this->dbg;

FEATURE Example.h/Impl
private:
    void setupDebuggerInfo()
    {
        osgcpe::DebugGetter
            localTime(
                "Local time",
                [this] {
                    auto tm = time(0);
                    auto now = localtime(&tm);
                    return asctime(now);
                }
            );
        this->dbg->addItem("info", localTime);
    }
    void setupDebuggerBGColor()
    {
        osgcpe::DebugSetter
            red(
                "Red",
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
        this->dbg->addItem("scene", red);
    }


FEATURE Example.h/Setup
this->setupBoxRotation();

FEATURE Example.h/TearDown
this->tearBoxRotationDown();

FEATURE Example.h/Impl
private:
    const std::string boxRotationCallbackName = "BoxRotation";
    void setupBoxRotation()
    {
        // Listen to box selection.
        this->boxSelected.addCallback(
            [&] {
                this->rotateBox();
            },
            this->boxRotationCallbackName
        );
    }
    void tearBoxRotationDown()
    {
        this->boxSelected.removeCallback(this->boxRotationCallbackName);
    }
    void rotateBox()
    {
        OSGCPE_EXAMPLE_LOG("TODO rotateBox");
    }

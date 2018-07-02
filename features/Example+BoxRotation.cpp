FEATURE Example.h/Setup
this->setupBoxRotation();

FEATURE Example.h/TearDown
this->tearBoxRotationDown();

FEATURE Example.h/Impl
private:
    const std::string boxRotationCallbackName = "BoxRotation";
    void setupBoxRotation()
    {
        // Do nothing for an empty scene.
        if (!this->scene.valid())
        {
            return;
        }

        // Start box rotation upon box selection.
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
        this->stopBoxRotationAnimation();
    }
    scene::LinearInterpolator interpolator;
    osg::Timer rotationTimer;
    void rotateBox()
    {
        OSGCPE_EXAMPLE_LOG("TODO rotateBox");

        // Get current box rotation along X.
        // This is now interpolation starting point: source.
        auto rot = scene::simpleRotation(this->scene);
        auto srcX = rot.x();
        // Calculate desired box rotation along X.
        // This is now interpolation finish point: destination.
        auto dstX = srcX + 45;

        // Configure interpolation.
        this->interpolator.keyValues = {
            {0, srcX},
            {1, dstX},
        };

        this->startBoxRotationAnimation();
    }
    void animateBoxRotation()
    {
        float elapsed = this->rotationTimer.time_s();
        auto lastKeyValue = this->interpolator.keyValues.back();
        float stopTime = lastKeyValue.key;
        // Stop animation.
        if (elapsed > stopTime)
        {
            this->setBoxRotationX(lastKeyValue.value);
            this->stopBoxRotationAnimation();
            OSGCPE_EXAMPLE_LOG("stop animation");
            return;
        }
        // Animate.
        auto value = this->interpolator.valueFor(elapsed);
        this->setBoxRotationX(value);
    }
    void setBoxRotationX(float x)
    {
        auto rot = scene::simpleRotation(this->scene);
        rot.x() = x;
        scene::setSimpleRotation(this->scene, rot);
    }
    void startBoxRotationAnimation()
    {
        // Reset timer.
        this->rotationTimer.setStartTick();
        // Subscribe to frame ticks.
        this->app->frameReporter.addCallback(
            [&] {
                this->animateBoxRotation();
            },
            this->boxRotationCallbackName
        );
    }
    void stopBoxRotationAnimation()
    {
        // Unsubscribe from frame ticks.
        this->app->frameReporter.removeCallback(this->boxRotationCallbackName);
    }

FEATURE core.h/Setup
this->setupBoxRotation();

FEATURE core.h/TearDown
this->tearBoxRotationDown();

FEATURE core.h/Impl
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
        // Get current box rotation along X.
        auto rot = scene::simpleRotation(this->scene);
        auto srcX = rot.x();

        // Configure interpolation.
        this->interpolator.keyValues = {
            {0, srcX},
            {0.5, srcX + 45}, // Rotate by 45 degrees in 0.5 seconds.
            {2, srcX}, // Rotate back in 2 - 0.5 = 1.5 seconds.
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

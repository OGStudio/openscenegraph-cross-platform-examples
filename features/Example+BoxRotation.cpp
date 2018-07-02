FEATURE Example.h/Setup
this->setupBoxRotation();

FEATURE Example.h/TearDown
this->tearBoxRotationDown();

FEATURE Example.h/Impl
private:
    const std::string boxRotationCallbackName = "BoxRotation";
    osg::Vec3f boxRotation;
    void setupBoxRotation()
    {
        // Do nothing for an empty scene.
        if (!this->scene.valid())
        {
            return;
        }

        // Record current box rotation.
        this->boxRotation = scene::simpleRotation(this->scene);
        // Listen to box selection.
        this->boxSelected.addCallback(
            [&] {
                this->rotateBox();
            },
            this->boxRotationCallbackName
        );

        // TODO CHECK INTERPOLATION BEFORE ANIMATING

        scene::LinearInterpolator interpolator;
        interpolator.keyValues = {
            {0, 0},
            {2, 10},
        };

        float key = 0.5;
        float value = interpolator.valueFor(key);

        OSGCPE_EXAMPLE_LOG("key: '%f' interpolated value: '%f'", key, value);

    }
    void tearBoxRotationDown()
    {
        this->boxSelected.removeCallback(this->boxRotationCallbackName);
    }
    void rotateBox()
    {
        OSGCPE_EXAMPLE_LOG("TODO rotateBox");
        this->boxRotation.x() += 10;
        scene::setSimpleRotation(this->scene, this->boxRotation);

        auto rot = scene::simpleRotation(this->scene);
        OSGCPE_EXAMPLE_LOG(
            "Current rotation: '%f, %f, %f'",
            rot.x(),
            rot.y(),
            rot.z()
        );
    }

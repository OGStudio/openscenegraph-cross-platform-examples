FEATURE main.h/Setup
this->setupSequenceTest();

FEATURE main.h/TearDown
this->tearSequenceTestDown();

FEATURE main.h/Impl
private:
    core::Sequence sequence;
    const std::string boxRotationCallbackName = "BoxRotation";
    const float rotationStepDegrees = 5;
    core::Reporter loadingSimulated;
    const std::string loadingSimulationCallbackName = "LoadingSimulation";

    core::Reporter bgChanged;
    const std::string bgChangeCallbackName = "BGChange";
    const osg::Vec4 bgColorDefault = {0.192, 0.192, 0.388, 0};
    const osg::Vec4 bgColorDim = {0.192, 0.192, 0.192, 0};
    const float bgColorStepDiff = 0.0049;

    void setupSequenceTest()
    {
        // Do nothing for an empty scene.
        if (!this->scene.valid())
        {
            return;
        }

        this->sequence.setActions({
            CORE_SEQUENCE_ACTION(
                "enableBoxSelection",
                this->setBoxSelectionEnabled(true)
            ),
            CORE_SEQUENCE_ACTION(
                "waitForBoxSelection",
                this->waitForBoxSelection()
            ),
            CORE_SEQUENCE_ACTION(
                "disableBoxSelection",
                this->setBoxSelectionEnabled(false)
            ),
            CORE_SEQUENCE_ACTION(
                "dimBackground",
                this->changeBackground(true)
            ),
            CORE_SEQUENCE_ACTION(
                "startBoxRotation",
                this->setBoxRotationEnabled(true)
            ),
            CORE_SEQUENCE_ACTION(
                "simulateLoading",
                this->simulateLoading()
            ),
            CORE_SEQUENCE_ACTION(
                "stopBoxRotation",
                this->setBoxRotationEnabled(false)
            ),
            CORE_SEQUENCE_ACTION(
                "lightBackground",
                this->changeBackground(false)
            ),
        });

        // Enable sequence.
        this->sequence.isRepeatable = true;
        this->sequence.setEnabled(true);
    }
    void tearSequenceTestDown()
    {
        this->sequence.setEnabled(false);
    }

    // Box selection.
    core::Reporter *setBoxSelectionEnabled(bool state)
    {
        if (state)
        {
            this->setupBoxSelection();
        }
        else
        {
            this->tearBoxSelectionDown();
        }

        return 0;
    }
    core::Reporter *waitForBoxSelection()
    {
        return &this->boxSelected;
    }

    // Box rotation.
    void rotateBox()
    {
        auto rot = scene::simpleRotation(this->scene);
        rot.z() += this->rotationStepDegrees;
        scene::setSimpleRotation(this->scene, rot);
    }
    core::Reporter *setBoxRotationEnabled(bool state)
    {
        // Subscribe to `frameReporter`.
        if (state)
        {
            this->app->frameReporter.addCallback(
                [&] {
                    this->rotateBox();
                },
                this->boxRotationCallbackName
            );
        }
        // Unsubscribe from `frameReporter`.
        else
        {
            this->app->frameReporter.removeCallback(
                this->boxRotationCallbackName
            );
        }

        return 0;
    }

    // Loading simulation.
    core::Reporter *simulateLoading()
    {
        // Simulate loading for 2 seconds.
        int duration = 2;
        auto startDt = time(0);

        this->app->frameReporter.addCallback(
            [=] {
                auto nowDt = time(0);
                auto elapsed = nowDt - startDt;
                if (elapsed >= duration)
                {
                    this->app->frameReporter.removeCallback(this->loadingSimulationCallbackName);
                    this->loadingSimulated.report();
                }
            },
            this->loadingSimulationCallbackName
        );

        return &this->loadingSimulated;
    }

    // Background.
    core::Reporter *changeBackground(bool dim)
    {
        auto targetColor = 
            dim ?
            this->bgColorDim :
            this->bgColorDefault
            ;
        auto targetColorDiff =
            dim ?
            -this->bgColorStepDiff :
            this->bgColorStepDiff
            ;
        this->app->frameReporter.addCallback(
            [=] {
                // Change color.
                auto color = this->app->camera()->getClearColor();
                color.z() += targetColorDiff;
                this->app->camera()->setClearColor(color);

                // Find out if we're done.
                auto targetColorHasBeenReached =
                    abs(color.z() - targetColor.z()) < 0.01;
                if (targetColorHasBeenReached)
                {
                    this->app->frameReporter.removeCallback(this->bgChangeCallbackName);
                    this->app->camera()->setClearColor(targetColor);
                    this->bgChanged.report();
                }
            },
            this->bgChangeCallbackName
        );

        return &this->bgChanged;
    }

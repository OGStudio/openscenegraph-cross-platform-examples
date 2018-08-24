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

    void setupSequenceTest()
    {
        // Do nothing for an empty scene.
        if (!this->scene.valid())
        {
            return;
        }

        this->sequence.setActions({
            "enableBoxSelection",
            "waitForBoxSelection",
            "disableBoxSelection",
            //"dimBackground",
            "startBoxRotation",
            "simulateLoading",
            "stopBoxRotation",
            //"lightBackground",
        });

        // Register actions.
        OSGCPE_CORE_REGISTER_SEQUENCE_ACTION(
            this->sequence,
            "waitForBoxSelection",
            this->waitForBoxSelection()
        );
        OSGCPE_CORE_REGISTER_SEQUENCE_ACTION(
            this->sequence,
            "enableBoxSelection",
            this->setBoxSelectionEnabled(true)
        );
        OSGCPE_CORE_REGISTER_SEQUENCE_ACTION(
            this->sequence,
            "disableBoxSelection",
            this->setBoxSelectionEnabled(false)
        );
        OSGCPE_CORE_REGISTER_SEQUENCE_ACTION(
            this->sequence,
            "startBoxRotation",
            this->setBoxRotationEnabled(true)
        );
        OSGCPE_CORE_REGISTER_SEQUENCE_ACTION(
            this->sequence,
            "stopBoxRotation",
            this->setBoxRotationEnabled(false)
        );
        OSGCPE_CORE_REGISTER_SEQUENCE_ACTION(
            this->sequence,
            "simulateLoading",
            this->simulateLoading()
        );
        /*
        OSGCPE_CORE_REGISTER_SEQUENCE_ACTION(
            this->sequence,
            "dimBackground",
            this->dimBackground()
        );
        OSGCPE_CORE_REGISTER_SEQUENCE_ACTION(
            this->sequence,
            "lightBackground",
            this->lightBackground()
        );
        */

        // Enable sequence.
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

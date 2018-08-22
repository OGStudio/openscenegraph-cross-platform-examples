FEATURE main.h/Setup
this->setupSequenceTest();

FEATURE main.h/TearDown
this->tearSequenceTestDown();

FEATURE main.h/Impl
private:
    const std::string sequenceTestCallbackName = "SequenceTest";
    void setupSequenceTest()
    {
        // Do nothing for an empty scene.
        if (!this->scene.valid())
        {
            return;
        }

        this->setSequenceTestBoxSelectionEnabled(true);
    }
    void tearSequenceTestDown()
    {
        this->setSequenceTestBoxSelectionEnabled(false);
        // TODO Terminate animations?
    }
    void setSequenceTestBoxSelectionEnabled(bool state)
    {
        if (state)
        {
            this->boxSelected.addCallback(
                [&] {
                    this->testSequence();
                },
                this->sequenceTestCallbackName
            );
        }
        else
        {
            this->boxSelected.removeCallback(this->sequenceTestCallbackName);
        }
    }
    void testSequence()
    {
        OSGCPE_MAIN_EXAMPLE_LOG("TODO test sequence");
        // TODO Disable selection while sequence test is in progress. Do it through Sequence, too.
    }

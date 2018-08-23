FEATURE main.h/Setup
this->setupSequenceTest();

FEATURE main.h/TearDown
this->tearSequenceTestDown();

FEATURE main.h/Impl
private:
    const std::string sequenceTestCallbackName = "SequenceTest";
    core::Sequence sequence;
    void setupSequenceTest()
    {
        // Do nothing for an empty scene.
        if (!this->scene.valid())
        {
            return;
        }

        OSGCPE_MAIN_EXAMPLE_REGISTER_SEQUENCE_ACTION(sequence, "waitForBoxSelection", this->waitForBoxSelection());
        // Register actions.
        sequence.registerAction(
            "waitForBoxSelection",
            OSGCPE_CORE_SEQUENCE_CALLBACK(this->waitForBoxSelection())
        );
        sequence.registerAction(
            "printBoxSelection",
            OSGCPE_CORE_SEQUENCE_CALLBACK(this->printBoxSelection())
        );

        sequence.setActionSequence({
            "enableBoxSelection",
            "waitForBoxSelection",
            "disableBoxSelection",
            "printBoxSelection",
            "enableBoxSelection",
            /*
            "startLoading",
            "startBoxRotation",
            "waitForLoadingFinish",
            "stopBoxRotation",
            "depictLoadingResult",
            */
        });

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
        /*
        sequence.registerAction(
            "disableBoxSelection",
            OSGCPE_SEQUENCE_CALLBACK(this->setBoxSelectionEnabled(false))
        );
        sequence.registerAction(
            "enableBoxSelection",
            OSGCPE_SEQUENCE_CALLBACK(this->setBoxSelectionEnabled(true))
        );
        sequence.registerAction(
            "startLoading",
            OSGCPE_SEQUENCE_CALLBACK(this->startLoading())
        );
        sequence.registerAction(
            "startBoxRotation",
            OSGCPE_SEQUENCE_CALLBACK(this->startBoxRotation())
        );
        */
        sequence.setEnabled(true);
        // TODO Finish registration of actions.

    }
    core::Reporter *waitForBoxSelection()
    {
        return &this->boxSelected;
    }
    core::Reporter *printBoxSelection()
    {
        OSGCPE_MAIN_EXAMPLE_LOG("printBoxSelection: box has been selected");
        return 0;
    }
/*
        void setupMatching()
        {
            this->matchReport.setDebugName("match");
            this->matchSequence.setDebugName("match");
            this->missSequence.setDebugName("miss");

            // Colors for BG color animation in case of match.
            auto start = GAME_BG_COLOR_DEFAULT;
            auto target = GAME_BG_COLOR_MATCH;
            float duration = GAME_BG_ANIM_MATCH_DURATION;

            // Successful match sequence.
            this->matchSequence
                .subscribe(&this->matchReport)
                // If we have a match.
                .call(MJIN_REPORT_TRUE(this->hasMatch()))
                // Disable node picking.
                .call(MJIN_REPORT_ONCE(this->setPickingEnabled(false)))

                // Reset BG timer, subscribe to ticks, and animate BG color.
                .call(MJIN_REPORT_ONCE(this->resetBGTimer()))
                .subscribe(&this->tickReport)
                .call(MJIN_REPORT_MANY(this->animateBG(start, target, duration)))
                .unsubscribe(&this->tickReport)

                // Animate removal of the first selected node.
                .call(MJIN_REPORT_ONCE(this->setupRemoval()))
                .subscribe(&this->tickReport)
                .call(MJIN_REPORT_MANY(this->animateRemoval()))
                .unsubscribe(&this->tickReport)
                // Delete the node.
                .call(MJIN_REPORT_ONCE(this->removeNode()))

                // Animate removal of the second selected node.
                .call(MJIN_REPORT_ONCE(this->setupRemoval()))
                .subscribe(&this->tickReport)
                .call(MJIN_REPORT_MANY(this->animateRemoval()))
                .unsubscribe(&this->tickReport)
                // Delete the node.
                .call(MJIN_REPORT_ONCE(this->removeNode()))

                // De-animate BG color back to its initial value.
                .call(MJIN_REPORT_ONCE(this->resetBGTimer()))
                .subscribe(&this->tickReport)
                .call(MJIN_REPORT_MANY(this->animateBG(target, start, duration)))
                .unsubscribe(&this->tickReport)
                
                // Enable node picking.
                .call(MJIN_REPORT_ONCE(this->setPickingEnabled(true)))

                // Exit if no items left.
                .call(MJIN_REPORT_ONCE(this->exitIfNoItems()))
                ;

            // Colors for BG color animation in case of miss.
            target = GAME_BG_COLOR_MISS;
            duration = GAME_BG_ANIM_MISS_DURATION;

            // Miss sequence.
            this->missSequence
                .subscribe(&this->matchReport)
                // If we have a miss.
                .call(MJIN_REPORT_TRUE(!this->hasMatch()))
                // Disable node picking.
                .call(MJIN_REPORT_ONCE(this->setPickingEnabled(false)))

                // Reset BG timer, subscribe to ticks, and animate BG color.
                .call(MJIN_REPORT_ONCE(this->resetBGTimer()))
                .subscribe(&this->tickReport)
                .call(MJIN_REPORT_MANY(this->animateBG(start, target, duration)))
                .unsubscribe(&this->tickReport)
                // De-animate BG color back to its initial value.
                .call(MJIN_REPORT_ONCE(this->resetBGTimer()))
                .subscribe(&this->tickReport)
                .call(MJIN_REPORT_MANY(this->animateBG(target, start, duration)))
                .unsubscribe(&this->tickReport)

                // Animate BG color once again.
                .call(MJIN_REPORT_ONCE(this->resetBGTimer()))
                .subscribe(&this->tickReport)
                .call(MJIN_REPORT_MANY(this->animateBG(start, target, duration)))
                .unsubscribe(&this->tickReport)
                // De-animate BG color back once again.
                .call(MJIN_REPORT_ONCE(this->resetBGTimer()))
                .subscribe(&this->tickReport)
                .call(MJIN_REPORT_MANY(this->animateBG(target, start, duration)))
                .unsubscribe(&this->tickReport)

                // Deselect all nodes.
                .call(MJIN_REPORT_ONCE(this->deselectAllNodes()))
                // Enable node picking.
                .call(MJIN_REPORT_ONCE(this->setPickingEnabled(true)))
                ;
        }
*/

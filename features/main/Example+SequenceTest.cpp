FEATURE main.h/Setup
this->setupSequenceTest();

FEATURE main.h/TearDown
this->tearSequenceTestDown();

FEATURE main.h/Impl
private:
    const std::string sequenceTestBoxSelectedCallbackName =
        "SequenceTestBoxSelected";
    core::Reporter sequenceTestBoxSelected;
    core::Sequence sequence;

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
            "printBoxSelection",
            /*
            "startLoading",
            "startBoxRotation",
            "waitForLoadingFinish",
            "stopBoxRotation",
            "depictLoadingResult",
            */
        });

        // Register actions.
        OSGCPE_CORE_REGISTER_SEQUENCE_ACTION(
            this->sequence,
            "waitForBoxSelection",
            this->sequenceTestWaitForBoxSelection()
        );
        OSGCPE_CORE_REGISTER_SEQUENCE_ACTION(
            this->sequence,
            "printBoxSelection",
            this->sequenceTestPrintBoxSelection()
        );
        OSGCPE_CORE_REGISTER_SEQUENCE_ACTION(
            this->sequence,
            "enableBoxSelection",
            this->sequenceTestSetBoxSelectionEnabled(true)
        );
        OSGCPE_CORE_REGISTER_SEQUENCE_ACTION(
            this->sequence,
            "disableBoxSelection",
            this->sequenceTestSetBoxSelectionEnabled(false)
        );
        /*
            "startLoading",
            "startBoxRotation",
        */

        // Enable sequence.
        this->sequence.setEnabled(true);
    }
    void tearSequenceTestDown()
    {
        this->sequence.setEnabled(false);
    }
    core::Reporter *sequenceTestSetBoxSelectionEnabled(bool state)
    {
        // Subscribe to `boxSelected`.
        if (state)
        {
            this->boxSelected.addCallback(
                [&] {
                    this->sequenceTestBoxSelected.report();
                },
                this->sequenceTestBoxSelectedCallbackName
            );
        }
        // Unsubscribe from `boxSelected`.
        else
        {
            this->boxSelected.removeCallback(this->sequenceTestBoxSelectedCallbackName);
        }

        return 0;
    }
    /*
    void setSequenceTestBoxSelectionEnabled(bool state)
    {
        if (state)
        {
            this->boxSelected.addCallback(
                [&] {
                    //this->testSequence();
                },
                this->sequenceTestCallbackName
            );
        }
        else
        {
            this->boxSelected.removeCallback(this->sequenceTestCallbackName);
        }
    }
    */
    core::Reporter *sequenceTestWaitForBoxSelection()
    {
        return &this->sequenceTestBoxSelected;
    }
    core::Reporter *sequenceTestPrintBoxSelection()
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

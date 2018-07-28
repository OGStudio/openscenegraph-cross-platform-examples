FEATURE main.h/Setup
this->setupBoxSelection();

FEATURE main.h/TearDown
this->tearBoxSelectionDown();

FEATURE main.h/Impl
private:
    core::Reporter boxSelected;
    const std::string boxSelectionCallbackName = "BoxSelection";
    const unsigned int selectionNodeMask = 0x00000004;
    void setupBoxSelection()
    {
        // Make box node selectable by excluding specific node mask.
        this->scene->setNodeMask(
            this->scene->getNodeMask() & ~this->selectionNodeMask
        );

        // Listen to mouse clicks.
        this->app->mouse->pressedButtonsChanged.addCallback(
            [&] {
                bool clicked = !this->app->mouse->pressedButtons.empty();
                if (clicked)
                {
                    this->tryToSelectBox();
                }
            },
            this->boxSelectionCallbackName
        );
    }
    void tearBoxSelectionDown()
    {
        this->app->mouse->pressedButtonsChanged.removeCallback(
            this->boxSelectionCallbackName
        );
    }
    void tryToSelectBox()
    {
        auto node =
            scene::nodeAtPosition(
                this->app->mouse->position,
                this->app->camera(),
                this->selectionNodeMask
            );
        if (node)
        {
            // Since we don't have other nodes in the scene,
            // we are sure it's the box.
            this->boxSelected.report();
        }
    }

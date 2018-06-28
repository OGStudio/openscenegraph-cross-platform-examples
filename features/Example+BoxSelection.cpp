FEATURE Example.h/Setup
this->setupBoxSelection();

FEATURE Example.h/TearDown
this->tearBoxSelectionDown();

FEATURE Example.h/Impl
private:
    const std::string boxSelectionCallbackName = "BoxSelection";
    void setupBoxSelection()
    {
        // Listen to mouse clicks.
        this->app->mouse->pressedButtonsChanged.addCallback(
            [&] {
                bool clicked = this->app->mouse->pressedButtons.empty();
                if (clicked)
                {
                    OSGCPE_EXAMPLE_LOG("Clicked");
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

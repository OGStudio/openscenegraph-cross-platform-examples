FEATURE Example.h/Setup
this->setupSceneTexturing();

FEATURE Example.h/Impl
private:
    void setupSceneTexturing()
    {
        // Do nothing for an empty scene.
        if (!this->scene.valid())
        {
            return;
        }

        osgcpe::scene::paintScene(this->scene);
    }

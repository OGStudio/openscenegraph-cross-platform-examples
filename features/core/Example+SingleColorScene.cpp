FEATURE core.h/Setup
this->setupSceneTexturing();

FEATURE core.h/Impl
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

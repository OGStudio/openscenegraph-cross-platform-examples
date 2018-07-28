FEATURE main.h/Setup
this->setupSceneTexturing();

FEATURE main.h/Impl
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

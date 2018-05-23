FEATURE Application.h/Impl
public:
    void run()
    {
        while (!this->viewer->done())
        {
            this->frame();
        }
    }

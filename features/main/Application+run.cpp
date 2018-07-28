FEATURE main.h/Impl
public:
    void run()
    {
        while (!this->viewer->done())
        {
            this->frame();
        }
    }

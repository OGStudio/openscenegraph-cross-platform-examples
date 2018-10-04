FEATURE main.h/Setup
this->setupParameters(parameters);

FEATURE main.h/Impl
private:
    Parameters parameters;
    void setupParameters(const Parameters &parameters)
    {
        this->parameters = parameters;
    }

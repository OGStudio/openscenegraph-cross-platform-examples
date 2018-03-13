FEATURE Logger.h/Impl
#include <iostream>

// Log message using platform specific tools.
void platformLog(const char *message)
{
    std::cout << message << std::endl;
}

FEATURE logging.h/Include
#include <iostream>

FEATURE logging.h/Impl
// Log message using platform specific tools.
void platformLog(const char *message)
{
    std::cout << message << std::endl;
}

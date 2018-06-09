FEATURE log.h/Include
#include <iostream>

FEATURE log.h/Impl
//! Cross-platform logging function.
void log(const char *message)
{
    std::cout << message << std::endl;
}

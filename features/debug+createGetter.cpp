FEATURE debug.h/Include
#include <functional>

FEATURE debug.h/Impl
typedef std::function<void()> GetterCallback;

Getter createGetter(const std::string &title, GetterCallback callback)
{


}

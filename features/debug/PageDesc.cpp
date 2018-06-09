FEATURE debug.h/Include
#include <string>
#include <vector>

FEATURE debug.h/Impl
//! Provides serializable representation of a Page instance.
struct PageDesc
{
    std::string title;

    struct Item
    {
        std::string title;
        std::string value;
    };
    std::vector<Item> items;
};

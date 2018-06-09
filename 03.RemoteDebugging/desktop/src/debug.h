
/*
This file is part of OpenSceneGraph cross-platform examples:
  https://github.com/OGStudio/openscenegraph-cross-platform-examples

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUG_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUG_H

#include "debug-extlib.h"

// PageDesc Start
#include <string>
#include <vector>

// PageDesc End


namespace osgcpe
{
namespace debug
{

// PageDesc Start
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
// PageDesc End

// Page Start
//! Provides debug page with items to alter.
struct Page
{

    // SETUP.

    std::string title;

    Page(const std::string &title = "") : title(title) { }

    // ITEMS.

    typedef std::function<std::string()> GetterCallback;
    typedef std::function<void(const std::string &)> SetterCallback;

    struct Item
    {
        std::string title;
        GetterCallback getter;
        SetterCallback setter;
    };
    std::vector<Item> items;

    //! Convenience function to add items.
    void addItem(
        const std::string &title,
        GetterCallback getter,
        SetterCallback setter = nullptr
    ) {
        this->items.push_back({title, getter, setter});
    }

// Page End
    // Page+item Start
    Item *item(const std::string &title)
    {
        auto itemCount = this->items.size();
        for (auto i = 0; i < itemCount; ++i)
        {
            Item *item = &this->items[i];
            if (item->title == title)
            {
                return item;
            }
        }
        return 0;
    }
    // Page+item End
    // Page+setDesc Start
    void setDesc(const PageDesc& desc)
    {
        for (auto descItem : desc.items)
        {
            auto item = this->item(descItem.title);
            if (item && item->setter)
            {
                item->setter(descItem.value);
            }
        }
    }
    // Page+setDesc End
// Page Start
};
// Page End

} // namespace debug
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUG_H



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

// FEATURE Page+OSGCPE_DEBUG_PAGE_LOG/Impl

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

    // FEATURE Page+item/Impl
    // FEATURE Page+setDesc/Impl

};


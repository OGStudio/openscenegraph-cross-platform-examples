FEATURE debug.h/Begin
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

FEATURE debug.h/End
};

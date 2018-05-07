FEATURE Debugger.h/Include
#include <vector>

FEATURE Debugger.h/Impl
public:
    typedef std::function<std::string()> ItemGetterCallback;
    typedef std::function<void(const std::string &)> ItemSetterCallback;
private:
    struct Item
    {
        std::string title;
        ItemGetterCallback getter;
        ItemSetterCallback setter;
    };
    std::vector<Item> items;
public:
    void addItem(
        const std::string &title,
        ItemGetterCallback getter,
        ItemSetterCallback setter = nullptr
    ) {
        this->items.push_back({title, getter, setter});
    }

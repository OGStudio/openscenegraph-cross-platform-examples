FEATURE Page.h/Impl
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

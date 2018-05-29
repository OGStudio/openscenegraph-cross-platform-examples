FEATURE DebugPage.h/Impl
Item *item(const std::string &title)
{
    auto itemCount = this->items.size();
    for (auto i = 0; i < itemCount; ++i)
    {
        Item *item = &this->items[i];
        return item;
    }
    return 0;
}

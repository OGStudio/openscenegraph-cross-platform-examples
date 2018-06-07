FEATURE Page.h/Impl
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

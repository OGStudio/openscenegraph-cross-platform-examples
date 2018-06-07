FEATURE Debugger.h/Impl
public:
    Page *page(const std::string &title)
    {
        auto pageCount = this->pages.size();
        for (auto i = 0; i < pageCount; ++i)
        {
            Page *page = &this->pages[i];
            if (page->title == title)
            {
                return page;
            }
        }
        return 0;
    }

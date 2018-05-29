FEATURE Debugger.h/Impl
public:
    DebugPage *page(const std::string &title)
    {
        auto pageCount = this->pages.size();
        for (auto i = 0; i < pageCount; ++i)
        {
            DebugPage *page = &this->pages[i];
            if (page->title == title)
            {
                return page;
            }
        }
        return 0;
    }

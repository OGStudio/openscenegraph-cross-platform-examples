FEATURE debug.h/Impl
PageDesc jsonToPageDesc(const nlohmann::json &data)
{
    PageDesc desc;

    // Title.
    desc.title = data["title"].get<std::string>();

    // Convert JSON items to DebugPageDesc items.
    auto items = data["items"];
    for (auto item : items)
    {
        auto title = item["title"].get<std::string>();
        auto value = item["value"].get<std::string>();
        desc.items.push_back({ title, value });
    }

    return desc;
}

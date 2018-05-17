
// NOTE Consider moving debugger, debug page, debug page item parsing
// NOTE into separate files at some point.

const DebugPage = require("./DebugPage.js");
const DebugPageItem = require("./DebugPageItem.js");

function PARSING_LOG(message)
{
    console.log(`PARSING ${message}`);
}

function debuggerTitle(json)
{
    if (!json.hasOwnProperty("title"))
    {
        PARSING_LOG("ERROR Debugger title is missing");
        return "";
    }
    return json["title"];
}

function debugPageItem(json)
{
    if (!json.hasOwnProperty("title"))
    {
        PARSING_LOG("ERROR Debug page item title is missing");
        return null;
    }
    if (!json.hasOwnProperty("value"))
    {
        PARSING_LOG("ERROR Debug page item value is missing");
        return null;
    }
    const title = json["title"];
    const value = json["value"];
    var isWritable = null;
    if (json.hasOwnProperty("isWritable"))
    {
        isWritable = Number(json["isWritable"]);
    }
    var a = new DebugPageItem(title, value, isWritable);
    return a;
}

function debugPageItems(json)
{
    var items = [];
    if (!json.hasOwnProperty("items"))
    {
        PARSING_LOG("ERROR Debug page items are missing");
        return items;
    }
    for (var id in json["items"])
    {
        const itemJSON = json["items"][id];
        const item = debugPageItem(itemJSON);
        if (item != null)
        {
            items.push(item);
        }
    }
    return items;
}

function debugPage(json)
{
    if (!json.hasOwnProperty("title"))
    {
        PARSING_LOG("ERROR Debug page title is missing");
        return null;
    }
    const title = json["title"];
    const items = debugPageItems(json);
    return new DebugPage(title, items);
}

function debugPages(json)
{
    var pages = [];
    if (!json.hasOwnProperty("pages"))
    {
        PARSING_LOG("ERROR Debug pages are missing");
        return pages;
    }
    for (var id in json["pages"])
    {
        const pageJSON = json["pages"][id];
        const page = debugPage(pageJSON);
        if (page != null)
        {
            pages.push(page);
        }
    }

    return pages;
}


module.exports =
{
    debuggerTitle,
    debugPageItem,
    debugPageItems,
    debugPage,
    debugPages,
};


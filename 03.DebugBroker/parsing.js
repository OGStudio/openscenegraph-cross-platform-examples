
// NOTE Consider moving debugger, debug page, debug page item parsing
// NOTE into separate files at some point.

const DebugPage = require("./DebugPage.js");
const DebugPageItem = require("./DebugPageItem.js");

function PARSING_LOG(message)
{
    console.log(`PARSING ${message}`);
}

function debugPageItemToJSON(item)
{
    var string = JSON.stringify(item, null, 2);
    PARSING_LOG(`debugPageItemToJSON. item: '${string}'`);
    // Get latest value.
    const value = item.latestValue();
    return `{"title":"${item.title}","value":"${value}","isWritable":${item.isWritable}}`;
}

function debugPageItemsToJSON(items)
{
    var itemsJSON = "";
    for (var id in items)
    {
        // Add comma before adding second and following items.
        if (itemsJSON.length)
        {
            itemsJSON += ",";
        }
        const item = items [id];
        const itemJSON = debugPageItemToJSON(item);
        itemsJSON += itemJSON;
    }
    return "[" + itemsJSON + "]";
}

function debugPageToJSON(page)
{
    const itemsJSON = debugPageItemsToJSON(page.items);
    return `{"title":"${page.title}","items":${itemsJSON}}`;
}

function debugPagesToJSON(pages)
{
    var pagesJSON = "";
    for (var id in pages)
    {
        // Add comma before adding second and following items.
        if (pagesJSON.length)
        {
            pagesJSON += ",";
        }
        const page = pages[id];
        const pageJSON = debugPageToJSON(page);
        pagesJSON += pageJSON;
    }
    return "[" + pagesJSON + "]";
}

function debuggerToJSON(title, pages)
{
    const pagesJSON = debugPagesToJSON(pages);
    return `{"title":"${title}","pages":${pagesJSON}}`
}

function jsonToDebugPageItem(json)
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

function jsonToDebugPageItems(json)
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
        const item = jsonToDebugPageItem(itemJSON);
        if (item != null)
        {
            items.push(item);
        }
    }
    return items;
}

function jsonToDebugPage(json)
{
    if (!json.hasOwnProperty("title"))
    {
        PARSING_LOG("ERROR Debug page title is missing");
        return null;
    }
    const title = json["title"];
    const items = jsonToDebugPageItems(json);
    return new DebugPage(title, items);
}

function jsonToDebugPages(json)
{
    var pages = [];
    if (!json.hasOwnProperty("pages"))
    {
        // NOTE Not really an error if UI simply requests fields to display.
        //PARSING_LOG("ERROR Debug pages are missing");
        return pages;
    }
    for (var id in json["pages"])
    {
        const pageJSON = json["pages"][id];
        const page = jsonToDebugPage(pageJSON);
        if (page != null)
        {
            pages.push(page);
        }
    }

    return pages;
}

function jsonToDebuggerTitle(json)
{
    if (!json.hasOwnProperty("title"))
    {
        PARSING_LOG("ERROR Debugger title is missing");
        return "";
    }
    return json["title"];
}


module.exports =
{
    debuggerToJSON,
    jsonToDebugPages,
    jsonToDebuggerTitle,
};



class ItemLocation
{
    constructor(debuggerTitle, pageTitle, itemTitle)
    {
        this.debuggerTitle = debuggerTitle;
        this.pageTitle = pageTitle;
        this.itemTitle = itemTitle;
    }

}

function itemLocationToId(itemloc)
{
    return `${itemloc.debuggerTitle}-${itemloc.pageTitle}-${itemloc.itemTitle}`;
}

function idToItemLocation(id)
{
    const titles = id.split("-");
    return new ItemLocation(titles[0], titles[1], titles[2]);
}


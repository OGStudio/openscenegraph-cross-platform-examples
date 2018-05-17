
module.exports =
class DebugPage
{
    constructor(title, items)
    {
        this.title = title;
        this.items = items;
    }

    addItem(item)
    {
        this.items.push(item);
    }

    // Return item by title.
    item(title)
    {
        for (var item in this.items)
        {
            if (item.title == title)
            {
                return item;
            }
        }
        return null;
    }
}


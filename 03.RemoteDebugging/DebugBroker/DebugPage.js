
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
        for (var id in this.items)
        {
            var item = this.items[id];
            if (item.title == title)
            {
                return item;
            }
        }
        return null;
    }
}


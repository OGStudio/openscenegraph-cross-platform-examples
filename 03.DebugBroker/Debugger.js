
module.exports =
class Debugger
{
    constructor()
    {
        this.pages = { }
    }

    processDebugPage(page)
    {
        if (this.pageOriginIsApp(page))
        {
            this.processAppDebugPage(page);
        }
        else
        {
            this.processUIDebugPage(page);
        }
    }

    // Receive new pages and items from Application.
    processAppDebugPage(page)
    {
        const pageExists = (page.title in this.pages);
        // Accept everything if page does not yet exist.
        if (!pageExists)
        {
            this.pages[page.title] = page;
        }
        // Only accept new items for existing pages. Leave old items intact.
        else
        {
            var storedPage = this.pages[page.title];
            for (item in page.items)
            {
                const itemExists = storedPage.itemExists(item.title);
                if (!itemExists)
                {
                    storedPage.addItem(item);
                }
            }
        }
    }

    // Receive new values for existing pages and items from UI.
    processUIDebugPage(page)
    {
        const pageExists = (page.title in this.pages);
        // Ignore new page.
        if (!pageExists)
        {
            return;
        }
        var storedPage = this.pages[page.title];
        // Accept new values for existing items.
        for (item in page.items)
        {
            var storedItem = storedPage.item(item.title);
            // Item exists.
            if (storedItem != null)
            {
                // Accept new value.
                storedItem.value = item.value;
            }
        }
    }

    // Detect page origin.
    pageOriginIsApp(page)
    {
        // If any of debug page items has 'isWritable' property,
        // the page came from Application, not UI.
        for (var id in page.items)
        {
            var item = page.items[id];
            if (item.isWritable != null)
            {
                return true;
            }
        }
        return false;
    }

}


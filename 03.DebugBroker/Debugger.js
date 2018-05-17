
function DEBUGGER_LOG(message)
{
    console.log(`Debugger ${message}`);
}

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
            for (var id in page.items)
            {
                const item = page.items[id];
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
        // Accept new values for existing items that have 'isWritable = 1'.
        for (var id in page.items)
        {
            const item = page.items[id];
            var storedItem = storedPage.item(item.title);
            // Do nothing for items that are not writable.
            if (storedItem.isWritable != 1)
            {
                continue;
            }
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


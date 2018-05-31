
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
        // Accept new items for existing pages.
        // Only accept new values if
        // * they are different now
        // * they were changed by App, not UI
        else
        {
            var storedPage = this.pages[page.title];
            for (var id in page.items)
            {
                const item = page.items[id];
                const storedItem = storedPage.item(item.title);
                // Accept new item.
                if (!storedItem)
                {
                    storedPage.addItem(item);
                }
                // Accept value if new.
                else
                {
                    var appValue = storedItem.appValue;

                    var appValueString = JSON.stringify(appValue, null, 2);
                    DEBUGGER_LOG(`01.processAppDebugPage. appValue: '${appValueString}'`);
                    DEBUGGER_LOG(`02.processAppDebugPage. appValue.value: '${appValue.value}'`);

                    if (item.latestValue() != appValue.value)
                    {
                        DEBUGGER_LOG(`03.1.processAppDebugPage. assign appValue`);
                        appValue.value = item.latestValue();
                        appValue.dt = new Date();
                    }

                    appValueString = JSON.stringify(appValue, null, 2);
                    DEBUGGER_LOG(`04.processAppDebugPage. appValue: '${appValueString}'`);
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
            // Item exists.
            if (storedItem != null)
            {
                // Do nothing for items that are not writable.
                if (storedItem.isWritable != 1)
                {
                    continue;
                }
                // Accept value if new.
                var uiValue = storedItem.uiValue;
                if (item.latestValue() != uiValue.value)
                {
                    uiValue.value = item.latestValue();
                    uiValue.dt = new Date();
                }
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



const Debugger = require("./Debugger.js");
const parsing = require("./parsing.js");

function BROKER_LOG(message)
{
    console.log(`Broker ${message}`);
}

module.exports =
class Broker
{
    constructor()
    {
        this.debuggers = {}
    }

    process(json)
    {
        var string = JSON.stringify(json, null, 2);
        BROKER_LOG(`process: ${string}`);

        const title = parsing.debuggerTitle(json);
        const pages = parsing.debugPages(json);
        var dbg = this.debugger(title);
        for (var id in pages)
        {
            var page = pages[id];
            BROKER_LOG(`page title: ${page.title}`);
            var items = page.items;
            for (var itemId in items)
            {
                var item = items[itemId];
                BROKER_LOG(`item title: ${item.title}`);
            }
            //dbg.setDebugPage(pageTitle, items, app/ui flag/priority);
            // TODO isWritable detect UI/app side
        }
    }

    // Get or create Debugger instance.
    debugger(title)
    {
        if (!(title in this.debuggers))
        {
            this.debuggers[title] = new Debugger();
        }
        return this.debuggers[title];
    }

}


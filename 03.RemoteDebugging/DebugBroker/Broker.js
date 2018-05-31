
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

    // Process Application or UI initiated requests.
    process(json)
    {
        var string = JSON.stringify(json, null, 2);
        BROKER_LOG(`process: ${string}`);

        // Convert incoming JSON to DebugPages.
        const title = parsing.jsonToDebuggerTitle(json);
        const pages = parsing.jsonToDebugPages(json);
        var dbg = this.debugger(title);
        // Process DebugPages.
        for (var id in pages)
        {
            const page = pages[id];
            dbg.processDebugPage(page);
        }
        // Return updated Debugger state as JSON.
        return parsing.debuggerToJSON(title, dbg.pages);
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


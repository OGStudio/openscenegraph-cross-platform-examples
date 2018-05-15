
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
        console.log(`Broker.process: ${string}`);
        // Make sure debugger title exists.
        if (!json.hasOwnProperty("title")) {
            return "ERROR: Debugger title is missing";
        }
        // Create new debugger if does not yet exist.
        var title = json["title"];
        if (!(title in this.debuggers))
        {
            console.log(`Created debugger titled ${title}`);
            this.debuggers[title] = {}
        }
    }
}



const Broker = require("./Broker.js");

function APPLICATION_LOG(message)
{
    console.log(`Application ${message}`);
}

module.exports =
class Application
{
    constructor()
    {
        this.broker = new Broker();
    }

    processRequest(request, response)
    {
        const { method, url } = request;

        /*
         * Headers.
        for (var id in request.headers)
        {
            const header = request.headers[id];
            APPLICATION_LOG(`received header: '${id}=${header}'`)
        }
        */

        // Process "POST" requests.
        if (method === "POST")
        {
            var body = [];
            // Get body.
            request.on(
                "data",
                (chunk) => {
                    body.push(chunk);
                }
            ).on(
                "end",
                () => {
                    var sbody = Buffer.concat(body).toString();
                    APPLICATION_LOG(`body length: '${sbody.length}' body: '${sbody}'`);
                    var data = "nothing"
                    try
                    {
                        var json = JSON.parse(sbody);
                        data = this.broker.process(json);
                    }
                    catch (error)
                    {
                        APPLICATION_LOG(`Error: '${error}'`)
                    }
                    this.reply(response, data);
                }
            );
        }
        // Process other request.
        else
        {
            this.reply(response, "DebugBroker");
        }

    }

    reply(response, data)
    {
        response.statusCode = 200;
        response.setHeader("Content-Type", "application/json");
        // Allow CORS.
        response.setHeader("Access-Control-Allow-Origin", "*");
        response.setHeader("Access-Control-Allow-Headers", "Content-Type");
        response.end(data);
    }

}


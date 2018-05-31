
const Broker = require("./Broker.js");

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
                    body = Buffer.concat(body).toString();
                    var json = JSON.parse(body);
                    var data = this.broker.process(json);
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


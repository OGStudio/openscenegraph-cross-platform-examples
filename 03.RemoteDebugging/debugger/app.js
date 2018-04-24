
const http = require("http");
const hostname = "127.0.0.1";
const port = 7999;

// Mnaged global value.
var value = 1;

function returnValue(response)
{
    response.statusCode = 200;
    response.setHeader("Content-Type", "text/plain");
    response.end(`${value}`);
}

function processRequest(request, response)
{
    const { method, url } = request;
    console.log(`Got request. Method: ${method}. URL: ${url}`);

    // Set value.
    if (method === "POST")
    {
        var body = [];
        // Get body.
        request.on("data", (chunk) => {
            body.push(chunk);
        }).on("end", () => {
            body = Buffer.concat(body).toString();
            // Parse body.
            var newValue = Number(body);
            console.log(`New value: ${newValue}`);
            value = newValue;
            // Return value.
            returnValue(response);
        });
    }
    // Return value.
    else
    {
        returnValue(response);
    }

}

const server = http.createServer()
server.on("request", processRequest)
server.listen(port, hostname, () => {
    console.log(`Server running at http://${hostname}:${port}`);
})

// app+Stub Start
// Stub.
// app+Stub End


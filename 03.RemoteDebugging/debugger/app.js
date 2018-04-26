
const http = require("http");
const port = process.env.PORT || 7999;

// Mnaged global value.
var value = 1;

function returnValue(response)
{
    response.statusCode = 200;
    response.setHeader("Content-Type", "text/plain");
    // Allow CORS.
    response.setHeader("Access-Control-Allow-Origin", "*");
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
server.listen(port, () => {
    console.log(`Server listening at port ${port}`);
})

// app+Stub Start
// Stub.
// app+Stub End


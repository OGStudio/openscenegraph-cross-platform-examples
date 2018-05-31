
const http = require("http");
const Application = require("./Application.js");
const port = process.env.PORT || 7999;

var app = new Application();
var server = http.createServer()

server.on(
    "request",
    (request, response) => {
        const { method, url } = request;
        console.log(`Got request. Method: ${method}. URL: ${url}`);
        app.processRequest(request, response);
    }
)
server.listen(
    port,
    () => {
        console.log(`Server listening at port ${port}`);
    }
)


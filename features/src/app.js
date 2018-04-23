
const http = require("http");
const hostname = "127.0.0.1";
const port = 7999;

const server = http.createServer()
server.on("request", (request, response) => {
        const { method, url } = request;
        console.log(`Got request. Method: ${method}. URL: ${url}`);

        response.statusCode = 200;
        response.setHeader("Content-Type", "text/plain");
        response.end("Hello, World\n");
    });

server.listen(port, hostname, () => {
    console.log(`Server running at http://${hostname}:${port}`);
})

// FEATURE app+Stub/Impl


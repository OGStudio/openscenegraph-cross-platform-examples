
const http = require("http");
const hostname = "127.0.0.1";
const port = 7999;

const server =
    http.createServer((request, response) => {
        response.statusCode = 200;
        response.setHeader("Content-Type", "text/plain");
        response.end("Hello, World\n");
    });

server.listen(port, hostname, () => {
    console.log(`Server running at http://${hostname}:${port}`);
})

// app+Stub Start
// Stub.
// app+Stub End


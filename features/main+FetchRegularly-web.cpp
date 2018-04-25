FEATURE main.cpp/Include
#include <emscripten/fetch.h>

FEATURE main.cpp/Impl
// Forward declaration.
void fetchValue();

void fetchSucceeded(emscripten_fetch_t *fetch)
{
    printf(
        "Fetch. Finished downloading '%llu' bytes from '%s'\n",
        fetch->numBytes,
        fetch->url
    );

    const int BUF_SIZE = 100;
    // Get the body.
    if (fetch->numBytes < BUF_SIZE)
    {
        char buf[BUF_SIZE];
        strncpy(buf, fetch->data, fetch->numBytes);
        buf[fetch->numBytes + 1] = '\0';
        std::string body(buf);
        printf("Fetch. Received value: '%s'\n", body.c_str());
    }
    else
    {
        printf("Fetch. Too much data. Cannot parse\n");
    }
    emscripten_fetch_close(fetch);
    // Perform new fetch.
    fetchValue();
}

void fetchFailed(emscripten_fetch_t *fetch)
{
    printf(
        "Fetch. Failed to download '%s'. HTTP status code: '%d'\n",
        fetch->url,
        fetch->status
    );
    emscripten_fetch_close(fetch);
    // Do not perform new fetches?
}

void fetchValue()
{
    // Create a request for a resource over HTTP.
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = fetchSucceeded;
    attr.onerror = fetchFailed;
    // Resource URL.
    auto url = "http://127.0.0.1:7999";
    // Perform the request.
    emscripten_fetch(&attr, url);
    printf("Fetch. Request value from '%s'\n", url);
}

FEATURE main.cpp/Run
// Start regular fetching.
fetchValue();

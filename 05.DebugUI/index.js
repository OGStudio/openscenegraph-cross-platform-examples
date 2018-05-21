
function INDEX_LOG(message)
{
    console.log(`Index ${message}`);
}

// Load dependencies upon page load.
// Call 'main' once dependencies have been loaded.
$(function() {
    // Topic: How to include multiple js files using jQuery $.getScript() method
    // Source: https://stackoverflow.com/a/11803418
    $.when(
        $.getScript("Debugger.js"),
        $.getScript("Navigation.js"),
        $.Deferred(
            (deferred) => {
                deferred.resolve();
            }
        )
    ).done(
        () => {
            main();
        }
    );
});

function main()
{
    const params = new URLSearchParams(window.location.search);

    const brokerURL = params.get("broker");
    setupBroker(brokerURL);
    const debuggerName = params.get("debugger");
    setupDebugger(brokerURL, debuggerName);

    if (brokerURL && debuggerName)
    {
        requestDebugPages(brokerURL, debuggerName);
    }
}

function setupBroker(url)
{
    list = "ul.broker";
    // Report missing broker.
    if (!url)
    {
        const urlSample = "http://localhost:7999";
        const note = 
            `Add 'broker=${urlSample}' parameter, where ` +
            `<strong>${urlSample}</strong> should have <strong>DebugBroker</strong> instance running`
            ;
        addListItem(list, "ERROR", "broker parameter is missing");
        addListItem(list, "NOTE", note);
        return;
    }
    // Display broker URL.
    addListItem(list, "URL", url);
}

function setupDebugger(brokerURL, debuggerName)
{
    list = "ul.debugger";
    // Report missing debugger.
    if (!debuggerName)
    {
        const nameSample = "app-title";
        const note =
            `Add 'debugger=${nameSample}' parameter, where ` +
            `<strong>${nameSample}</strong> should be Debugger instance name used by app`
            ;
        addListItem(list, "ERROR", "debugger parameter is missing");
        addListItem(list, "NOTE", note);
        return;
    }
    // Display debugger name.
    addListItem(list, "Title", debuggerName);
}

function requestDebugPages(brokerURL, debuggerName)
{
    const data = `{"title":"${debuggerName}"}`;
    var success = function(response) {
        INDEX_LOG(`successful response: ${response}`);
    }
    var failure = function(response) {
        INDEX_LOG(`failed response: ${response}`);
    }

    $.ajax(
        {
            url: brokerURL,
            type: "POST",
            dataType: "text",
            contentType: "application/json",
            processData: false,
            data: data,
            success: success,
            error: failure
        }
    );
}

function addListItem(list, title, value)
{
    var contents = $(list).html();
    contents += `<li><strong>${title}:</strong> ${value}</li>`;
    $(list).html(contents);
}


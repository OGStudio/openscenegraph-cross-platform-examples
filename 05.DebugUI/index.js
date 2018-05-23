
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

    // Do not proceed if both required parameters are missing.
    if (!(brokerURL && debuggerName))
    {
        return;
    }

    // Success callback.
    var success = function(response) {
        INDEX_LOG(`successful response: ${response}`);
        const reply = JSON.parse(response);
        // Display list of pages.
        const list = "ul.pages";
        const selectedPage = params.get("page");
        listPages(list, reply.pages, selectedPage);
        // Display selected page items. 
        if (selectedPage != null)
        {
            for (var id in reply.pages)
            {
                const page = reply.pages[id];
                if (page.title == selectedPage)
                {
                    const table = "table.items";
                    for (var id in page.items)
                    {
                        const item = page.items[id];
                        const itemId = `${debuggerName}${page.title}${item.title}`;
                        addTablePageItem(table, itemId, item.title, item.value, item.isWritable);
                    }
                }
            }
        }
        else
        {
            addListItem("ul.items", "NOTE", "Select page to see its items");
        }
    }
    // Failure callback.
    var failure = function(response) {
        var string = JSON.stringify(response, null, 2);
        //addListItem(list, "ERROR", `Failed response: '${string}'`);
        INDEX_LOG(`failed response: '${string}'`);
    }
    // Perform request.
    requestData(brokerURL, debuggerName, success, failure);
}

function setupBroker(url)
{
    const list = "ul.broker";
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
    const list = "ul.debugger";
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

/*
function setupSending()
{
    setupSendButton();

    $("#send").click(
        function() {
            alert("TODO send");
        }
    );

}
*/

function requestData(brokerURL, debuggerName, successCallback, failureCallback)
{
    const data = `{"title":"${debuggerName}"}`;
    $.ajax(
        {
            url: brokerURL,
            type: "POST",
            dataType: "text",
            contentType: "application/json",
            processData: false,
            data: data,
            success: successCallback,
            error: failureCallback
        }
    );
}

function addListItem(list, title, value)
{
    var contents = $(list).html();
    contents += `<li><strong>${title}:</strong> ${value}</li>`;
    $(list).html(contents);
}

function addListPage(list, title, url)
{
    var contents = $(list).html();
    contents += `<li><a href=${url}>${title}</a></li>`;
    $(list).html(contents);
}

function listPages(list, pages, selectedPage)
{
    // Get URL base without possible 'page' parameter.
    const params = new URLSearchParams(window.location.search);
    params.delete("page");
    const urlBase = window.location.pathname + "?" + params.toString();
    // Loop through pages.
    for (var id in pages)
    {
        const page = pages[id];
        const url = urlBase + `&page=${page.title}`;
        var title = page.title;
        // Explicitely mark selected page.
        if (selectedPage && selectedPage == page.title)
        {
            title += " (selected)";
        }
        addListPage(list, title, url);
    }
}

function addTablePageItem(table, id, title, value, isWritable)
{
    var contents = $(table).html();
    const itemTitle = `<td><strong>${title}</strong></td>`;
    var itemValue = `<td>${value}</td>`;
    var itemApplication = "";
    if (isWritable)
    {
        // Use text field.
        itemValue = `<td><input id="${id}" type="text" value="${value}"/></td>`;
        // Provide application button.
        /*
        const buttonId = `${id}send`;
        itemApplication = `<td><input id="abccameraRedBGColorsend" type="button" value="Apply"></input></td>`;
        // Add click reaction.
        const buttonStrId = `#${buttonId}`;
        INDEX_LOG(`button str id: '${buttonStrId}'`);
        $("#abccameraRedBGColorsend").click(
            function() {
                const id = $(buttonStrId).attr("valueId");
                alert(`TODO send value of '${id}'`);
            }
        );
        */
        itemApplication = `<td><input class="myid" type="button" value="Apply"/></td>`;
    }
    contents += `<tr>${itemTitle}${itemValue}${itemApplication}</tr>`;
    $(table).html(contents);
    if (isWritable)
    {
        // Add click reaction.
        INDEX_LOG("Assign myid click handler");
        $("#items").on("click", "tr.td.input.myid",
            function() {
                INDEX_LOG("myid click");
                alert(`TODO send value`);
            }
        );
    }
}


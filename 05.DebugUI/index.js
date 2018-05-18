
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

    // Report missing broker.
    if (!params.has("broker"))
    {
        const message = messageBrokerIsMissing(window.location);
        $("div.broker").html(message);
        return;
    }
    // Display broker address.
    $("div.broker").html(`Broker: ${params.get("broker")}`);

    //$("div.navigation").html("Here will be pages to select from");
    //$("div.navigation").html(`Has 'broker' param: ${params.has("broker")}`);
    //$("div.contents").html("Here will be selected page items to alter");
    //var navigation = new Navigation();
    //$("div.contents").html(navigation.value);

}

function messageBrokerIsMissing(host)
{
    const brokerURL = "localhost:7999";
    const expectedURL = host + "?broker=" + brokerURL;
    const message =
        "Broker: ERROR, broker is missing!" +
        "<br>" +
        `You should open this page as <a href=${expectedURL}>${expectedURL}</a>, where ` +
        `<strong>${brokerURL}</strong> should have <strong>DebugBroker</strong> running`
        ;
    return message;
}


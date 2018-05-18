
// Load dependencies upon page load.
// Call 'main' once dependencies have been loaded.
$(function() {
    // Topic: How to include multiple js files using jQuery $.getScript() method
    // Source: https://stackoverflow.com/a/11803418
    $.when(
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

    $("div.navigation").html("Here will be pages to select from");
    //$("div.contents").html("Here will be selected page items to alter");
    var navigation = new Navigation();
    $("div.contents").html(navigation.value);

}



function itemJSON(itemLocation, itemValue)
{
    const itemJSON = `{"title":"${itemLocation.itemTitle}","value":"${itemValue}"}`;
    const pageJSON = `{"title":"${itemLocation.pageTitle}","items":[${itemJSON}]}`;
    const debuggerJSON = `{"title":"${itemLocation.debuggerTitle}","pages":[${pageJSON}]}`;
    return debuggerJSON;
}


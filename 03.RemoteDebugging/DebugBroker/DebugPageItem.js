
const DebugPageItemValue = require("./DebugPageItemValue.js");

function DEBUG_PAGE_ITEM_LOG(message)
{
    console.log(`DebugPageItem ${message}`);
}

module.exports =
class DebugPageItem
{
    constructor(title, value, isWritable)
    {
        this.title = title;
        this.isWritable = isWritable;
        const now = new Date();
        this.appValue = new DebugPageItemValue(value, now);
        this.uiValue = new DebugPageItemValue(value, now);
    }

    latestValue()
    {
        const val = 
            (this.appValue.dt > this.uiValue.dt) ?
            this.appValue.value :
            this.uiValue.value
            ;
        DEBUG_PAGE_ITEM_LOG(`latestValue(): '${val}'`);
        return val;
    }

}


FEATURE DebugPage.h/Include
#include "DebugPageDesc.h"

FEATURE DebugPage.h/Impl
void setDesc(const DebugPageDesc& desc)
{
    for (auto descItem : desc.items)
    {
        auto item = this->item(descItem.title);
        if (item)
        {
            item->setter(descItem.value);
        }
    }
}

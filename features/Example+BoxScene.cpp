FEATURE Example.h/Include
#include "box.osgt.h"
#include "resources.h"

FEATURE Example.h/Impl
osgcpe::Resource box("models", "box.osgt", box_osgt, box_osgt_len);
auto scene = osgcpe::resources::node(box);
if (!scene.valid())
{
    OSGCPE_EXAMPLE_LOG("ERROR Could not load scene");
}

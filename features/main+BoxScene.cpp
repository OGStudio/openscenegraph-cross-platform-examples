FEATURE main.cpp/Include
#include "box.osgt.h"
#include "resources.h"

FEATURE main.cpp/Impl
osgcpe::Resource box("models", "box.osgt", box_osgt, box_osgt_len);
auto scene = osgcpe::resources::node(box);
if (!scene.valid())
{
    OSGCPE_MAIN_LOG("ERROR Could not load scene");
}

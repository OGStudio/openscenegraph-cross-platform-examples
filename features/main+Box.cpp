FEATURE main.cpp/Include
#include "box.osgt.h"
#include "resources.h"

FEATURE main.cpp/Impl
osgcpe::Resource box("box.osgt", box_osgt, box_osgt_len);
auto scene = resourceNode(box, "osgt");
if (!scene.valid())
{
    osgcpe::log::log("ERROR Could not load scene");
}

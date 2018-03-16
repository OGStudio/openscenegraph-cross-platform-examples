FEATURE main.cpp/Include
#include "box.osgt.h"

FEATURE main.cpp/Impl
osgcpe::Resource box("box.osgt", box_osgt, box_osgt_len);
auto scene = createScene(box);

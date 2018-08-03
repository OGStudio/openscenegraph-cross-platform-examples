FEATURE openscenegraphWrappers01.cpp/Impl
#include <osgDB/Registry>
USE_SERIALIZER_WRAPPER(Object)
USE_SERIALIZER_WRAPPER(Group)
USE_SERIALIZER_WRAPPER(MatrixTransform)
USE_SERIALIZER_WRAPPER(Node)
extern "C" void wrapper_serializer_library_osg(void) {}

FEATURE openscenegraphWrappersObject.cpp/Impl
#include "src/osgWrappers/serializers/osg/Object.cpp"

FEATURE openscenegraphWrappersGroup.cpp/Impl
#include "src/osgWrappers/serializers/osg/Group.cpp"

FEATURE openscenegraphWrappersMatrixTransform.cpp/Impl
#include "src/osgWrappers/serializers/osg/MatrixTransform.cpp"

FEATURE openscenegraphWrappersNode.cpp/Impl
#include "src/osgWrappers/serializers/osg/Node.cpp"


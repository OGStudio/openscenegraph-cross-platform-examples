
/*
This file is part of OpenSceneGraph cross-platform examples:
  https://github.com/OGStudio/openscenegraph-cross-platform-examples

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

// osg-desktop Start
#include "src/osg/glu/libtess/tess.cpp"
#include "src/osg/glu/libutil/error.cpp"
#include "src/osg/glu/libutil/mipmap.cpp"
#include "src/osg/AlphaFunc.cpp"
#include "src/osg/ApplicationUsage.cpp"
#include "src/osg/AttributeDispatchers.cpp"
#include "src/osg/Array.cpp"
#include "src/osg/ArgumentParser.cpp"
#include "src/osg/Billboard.cpp"
#include "src/osg/BlendFunc.cpp"
#include "src/osg/BufferObject.cpp"
#include "src/osg/Callback.cpp"
#include "src/osg/Camera.cpp"
#include "src/osg/CameraView.cpp"
#include "src/osg/ColorMask.cpp"
#include "src/osg/CollectOccludersVisitor.cpp"
#include "src/osg/ComputeBoundsVisitor.cpp"
#include "src/osg/ContextData.cpp"
#include "src/osg/ConvexPlanarOccluder.cpp"
#include "src/osg/ConvexPlanarPolygon.cpp"
#include "src/osg/CoordinateSystemNode.cpp"
#include "src/osg/CopyOp.cpp"
#include "src/osg/CullingSet.cpp"
#include "src/osg/CullSettings.cpp"
#include "src/osg/CullStack.cpp"
#include "src/osg/Depth.cpp"
#include "src/osg/DisplaySettings.cpp"
#include "src/osg/Drawable.cpp"
#include "src/osg/dxtctool.cpp"
#include "src/osg/FrameBufferObject.cpp"
#include "src/osg/FrameStamp.cpp"
#include "src/osg/Geode.cpp"
#include "src/osg/Geometry.cpp"
#include "src/osg/GLExtensions.cpp"
#include "src/osg/GLObjects.cpp"
#include "src/osg/GraphicsContext.cpp"
#include "src/osg/GraphicsCostEstimator.cpp"
#include "src/osg/GraphicsThread.cpp"
#include "src/osg/Group.cpp"
#include "src/osg/Image.cpp"
#include "src/osg/ImageSequence.cpp"
#include "src/osg/ImageStream.cpp"
#include "src/osg/KdTree.cpp"
#include "src/osg/Light.cpp"
#include "src/osg/LightModel.cpp"
#include "src/osg/LOD.cpp"
#include "src/osg/Material.cpp"
#include "src/osg/Math.cpp"
//#include "src/osg/Matrixd.cpp"
#include "src/osg/Matrixf.cpp"
//#include "src/osg/Matrix_implementation.cpp"
#include "src/osg/MatrixTransform.cpp"
#include "src/osg/Node.cpp"
#include "src/osg/NodeVisitor.cpp"
#include "src/osg/Notify.cpp"
#include "src/osg/Object.cpp"
#include "src/osg/Observer.cpp"
#include "src/osg/ObserverNodePath.cpp"
#include "src/osg/OccluderNode.cpp"
#include "src/osg/OcclusionQueryNode.cpp"
#include "src/osg/OperationThread.cpp"
#include "src/osg/PagedLOD.cpp"
#include "src/osg/PolygonStipple.cpp"
#include "src/osg/PolygonMode.cpp"
#include "src/osg/PolygonOffset.cpp"
#include "src/osg/PrimitiveSet.cpp"
#include "src/osg/Program.cpp"
#include "src/osg/ProxyNode.cpp"
#include "src/osg/Quat.cpp"
#include "src/osg/Referenced.cpp"
#include "src/osg/Sequence.cpp"
#include "src/osg/Shader.cpp"
#include "src/osg/ShaderComposer.cpp"
#include "src/osg/Shape.cpp"
#include "src/osg/ShapeDrawable.cpp"
#include "src/osg/ShadowVolumeOccluder.cpp"
#include "src/osg/State.cpp"
#include "src/osg/StateAttribute.cpp"
#include "src/osg/StateSet.cpp"
#include "src/osg/Stats.cpp"
#include "src/osg/Stencil.cpp"
#include "src/osg/Switch.cpp"
#include "src/osg/TexEnv.cpp"
#include "src/osg/TexMat.cpp"
#include "src/osg/Texture.cpp"
#include "src/osg/Texture1D.cpp"
#include "src/osg/Texture2D.cpp"
#include "src/osg/Texture2DArray.cpp"
#include "src/osg/Texture2DMultisample.cpp"
#include "src/osg/Texture3D.cpp"
#include "src/osg/TextureCubeMap.cpp"
#include "src/osg/TextureRectangle.cpp"
#include "src/osg/Timer.cpp"
#include "src/osg/Transform.cpp"
#include "src/osg/Uniform.cpp"
#include "src/osg/UserDataContainer.cpp"
#include "src/osg/VertexArrayState.cpp"
#include "src/osg/View.cpp"
#include "src/osg/Viewport.cpp"
// osg-desktop End


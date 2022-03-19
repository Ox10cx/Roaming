#ifndef OSGHEADERFILES_H
#define OSGHEADERFILES_H

#include <android/log.h>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include<jni.h>

//osg
#include <osg/GL>
#include <osg/GLExtensions>
#include <osg/Depth>
#include <osg/BlendFunc>
#include <osg/BlendColor>
#include <osg/Program>
#include <osg/Shader>
#include <osg/Node>
#include <osg/Notify>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osgText/Text>
#include <osgText/Glyph>
#include <osg/LineStipple>
#include <osg/LineWidth>
#include <osg/Point>
#include <osg/StateSet>
#include <osg/StateAttribute>
#include <osg/Material>
#include <osg/NodeVisitor>
#include <osg/Array>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Quat>
#include <osg/Matrix>
#include <osg/Transform>
#include <osg/NodeCallback>
#include <osg/CullFace>
#include <osg/TexMat>
#include <osg/TexGen>
#include <osg/TexEnv>
#include <osg/TextureCubeMap>
#include <osg/ComputeBoundsVisitor>
#include <osg/PolygonOffset>
#include <osg/PolygonMode>
#include <osg/CullSettings>
#include <osg/LineSegment>

//osgDB
#include <osgDB/DatabasePager>
#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

//osg_viewer
#include <osgViewer/Viewer>
#include <osgViewer/Renderer>
#include <osgViewer/ViewerEventHandlers>

//osgText
#include <osgText/Text>
//osgGA

#include <osgGA/GUIEventAdapter>
#include <osgGA/MultiTouchTrackballManipulator>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/SphericalManipulator>

#include <osgUtil/Optimizer>
#include <osgUtil/LineSegmentIntersector>
#include <osgUtil/SmoothingVisitor>
#include <osgUtil/SceneView>
#include <osgUtil/Tessellator>
#include <osgUtil/IntersectVisitor>

//Static plugins Macro
USE_OSGPLUGIN(ive)
USE_OSGPLUGIN(osg)
USE_OSGPLUGIN(osg2)
USE_OSGPLUGIN(terrain)

USE_OSGPLUGIN(rgb)
USE_OSGPLUGIN(OpenFlight)
USE_OSGPLUGIN(freetype)
//USE_OSGPLUGIN(dds)

USE_OSGPLUGIN(tga)
USE_OSGPLUGIN(obj)
USE_OSGPLUGIN(jpeg)
USE_OSGPLUGIN(bmp)
//USE_OSGPLUGIN(png)


//Static DOTOSG
USE_DOTOSGWRAPPER_LIBRARY(osg)
USE_DOTOSGWRAPPER_LIBRARY(osgFX)
USE_DOTOSGWRAPPER_LIBRARY(osgParticle)
USE_DOTOSGWRAPPER_LIBRARY(osgTerrain)
USE_DOTOSGWRAPPER_LIBRARY(osgText)
USE_DOTOSGWRAPPER_LIBRARY(osgViewer)
USE_DOTOSGWRAPPER_LIBRARY(osgVolume)
//Static serializer
USE_SERIALIZER_WRAPPER_LIBRARY(osg)
USE_SERIALIZER_WRAPPER_LIBRARY(osgAnimation)
USE_SERIALIZER_WRAPPER_LIBRARY(osgFX)
USE_SERIALIZER_WRAPPER_LIBRARY(osgManipulator)
USE_SERIALIZER_WRAPPER_LIBRARY(osgParticle)
USE_SERIALIZER_WRAPPER_LIBRARY(osgTerrain)
USE_SERIALIZER_WRAPPER_LIBRARY(osgText)
USE_SERIALIZER_WRAPPER_LIBRARY(osgVolume)


#endif

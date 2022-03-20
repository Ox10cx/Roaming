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


class CScreenParam
{
public:
    int 					m_nWndWidth;     // view 的宽
    int 					m_nWndHeight;    // view 的高
    int 					m_nHdMapWidth;  // 高精度bitmap的宽
    int 					m_nHdMapHeight; // 高精度bitmap的高
    float 					m_fHdMapRatio; // ��ͼ��ʾ��Χ����
    float 					m_fAspect;
    float                   m_fTilt;
    float 					m_fCullRatio;
    float 					m_fScaleWidth;
    osg::Matrixd			m_VpwMatrix; //��������ת��Ļ�������
    osg::Matrixd            m_ViewMatrix;/**视图矩阵*/
    float					m_fVpwAngle;
    double					m_dVpwSin;
    double					m_dVpwCos;
    int                     m_nViewModel;
    int                     m_nCenterX;  /**地图中心点坐标X*/
    int                     m_nCenterY; /**地图中心点坐标Y*/
    float                   m_fCameraoffsetY;
};

typedef struct tagModelViewMatrix
{
    osg::Vec4f m_vPerspective;
    osg::Vec3f m_vCamera;
    osg::Vec3f m_vObserve;
    osg::Vec3f m_vUp;
    float      m_fMapRatio;
    float      m_CullRatio;
    int        m_CameraModel;
}ModelViewMatrix;

enum EViewModel
{
    eViewModel2D = 0,
    eViewModel3D = 1,
    eViewModelRoveIndoor=2,
    eViewModelRoveOutdoor=3,
    eViewModelNaviIndoor=4,
    eViewModelNaviOutdoor=5
};

#define MAX(a,b) ((a) > (b) ? (a):(b))
#define MIN(a,b) ((a) < (b) ? (a):(b))


#endif

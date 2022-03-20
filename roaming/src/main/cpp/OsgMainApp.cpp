//
// Created by 龚喜 on 2022/3/19.
//

#include  "OsgMainApp.h"

COsgMainApp::COsgMainApp() {
    m_Viewer =  new osgViewer::Viewer();
    m_pScreenParam                  = new CScreenParam();
    m_pScreenParam->m_fHdMapRatio   = 1.0f;
    m_pScreenParam->m_fAspect       = 1.0f;
    m_pScreenParam->m_fCullRatio    = 1.0f;
    m_pScreenParam->m_fScaleWidth   = 1.0f;
}

COsgMainApp::~COsgMainApp()
{
    if(m_pScreenParam)
    {
        delete m_pScreenParam;
    }
}
void COsgMainApp::InitOsgWindow(int width, int height, ModelViewMatrix initModelViewMatrix) {
    InitParameter(width, height, initModelViewMatrix.m_CameraModel);
    InitOsgRoot();
    SetCamera(initModelViewMatrix);
    m_Viewer->setSceneData(m_rpRootOsg.get());
    m_Viewer->realize();
}

/**
  * 初始化相关参数
  * return                        void
*/
void COsgMainApp::InitParameter(int width, int height, int model)
{
    m_pScreenParam->m_nWndWidth         = width;
    m_pScreenParam->m_nWndHeight        = height;
    m_pScreenParam->m_fAspect           = (double)width/(double)height;
    m_rpCamera  = m_Viewer->getCamera();
    osg::ref_ptr<osg::DisplaySettings> displaySettings=new osg::DisplaySettings;
    displaySettings->setNumMultiSamples(16);
    m_Viewer->setDisplaySettings(displaySettings.get());
    m_Viewer->setUpViewerAsEmbeddedInWindow(0, 0, width, height);
}

void COsgMainApp::InitOsgRoot()
{
    if(m_rpRootOsg == NULL) {
        m_rpRootOsg = new osg::Group();
        m_rpRoot =  new osg::Group();
        m_rpPositioned       = new osg::MatrixTransform;
        m_rpPositioned->addChild(m_rpRoot);
        m_rpRootOsg->addChild(m_rpPositioned);
    } else{
        m_rpRoot->removeChild(0, m_rpRoot->getNumChildren());
    }
}

void COsgMainApp::SetCamera(ModelViewMatrix initModelViewMatrix)
{
    LOGI("--COsgMain-- SetCamera %d",initModelViewMatrix.m_CameraModel);
    m_rpCamera->setComputeNearFarMode(osgUtil::CullVisitor::DO_NOT_COMPUTE_NEAR_FAR);
    m_rpCamera->setCullingMode(osg::CullSettings::VIEW_FRUSTUM_CULLING ||osg::CullSettings::SHADOW_OCCLUSION_CULLING ||osg::CullSettings::CLUSTER_CULLING );
    m_rpCamera->setCullingMode(m_rpCamera->getCullingMode()&~osg::CullSettings::SMALL_FEATURE_CULLING);

    m_rpCamera->setClearMask(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );

    m_rpCamera->setClearColor(osg::Vec4(231.0/255.0, 231.0/255.0, 231.0/255.0, 1.0));
    UpdateViewMatrix(initModelViewMatrix);
}

void COsgMainApp::UpdateViewMatrix(ModelViewMatrix updateViewMatrix)
{
    LOGI("UpdateViewMatrix [%f,%f,%f,%f],[%f,%f,%f],[%f,%f,%f] [%f,%f,%f] %f,%f,%d", updateViewMatrix.m_vPerspective._v[0], updateViewMatrix.m_vPerspective._v[1], updateViewMatrix.m_vPerspective._v[2], updateViewMatrix.m_vPerspective._v[3],
         updateViewMatrix.m_vCamera._v[0], updateViewMatrix.m_vCamera._v[1], updateViewMatrix.m_vCamera._v[2],
         updateViewMatrix.m_vObserve._v[0], updateViewMatrix.m_vObserve._v[1], updateViewMatrix.m_vObserve._v[2],
         updateViewMatrix.m_vUp._v[0], updateViewMatrix.m_vUp._v[1], updateViewMatrix.m_vUp._v[2],
         updateViewMatrix.m_fMapRatio, updateViewMatrix.m_CullRatio, updateViewMatrix.m_CameraModel);


    m_rpCamera->setProjectionMatrixAsPerspective(updateViewMatrix.m_vPerspective._v[0], updateViewMatrix.m_vPerspective._v[1],  updateViewMatrix.m_vPerspective._v[2], updateViewMatrix.m_vPerspective._v[3]);
    m_rpCamera->setViewMatrixAsLookAt(updateViewMatrix.m_vCamera, updateViewMatrix.m_vObserve, updateViewMatrix.m_vUp);
    m_pScreenParam->m_fCullRatio	= updateViewMatrix.m_CullRatio;
    m_pScreenParam->m_fHdMapRatio 	= updateViewMatrix.m_fMapRatio;
    m_pScreenParam->m_fCameraoffsetY =updateViewMatrix.m_vCamera._v[1]-updateViewMatrix.m_vObserve._v[1];
    m_pScreenParam->m_nViewModel    = updateViewMatrix.m_CameraModel;


    m_pScreenParam->m_ViewMatrix  = m_rpCamera->getViewMatrix();

    osg::Matrixd& viewMatrix=m_rpCamera->getViewMatrix();
    m_pScreenParam->m_VpwMatrix = m_rpCamera->getViewMatrix() * m_rpCamera->getProjectionMatrix() * m_rpCamera->getViewport()->computeWindowMatrix();

    m_pScreenParam->m_fVpwAngle	= 0.0f;

//    if(m_nModel == eViewModel2D)
//    {
//        m_pScreenParam->m_fVpwAngle	= 0.0f;
//    }
//    else
//    {
//        double dY = updateViewMatrix.m_vCamera._v[1] - updateViewMatrix.m_vObserve._v[1];
//        double dZ = updateViewMatrix.m_vObserve._v[2] - updateViewMatrix.m_vCamera._v[2];
//        if(dY < MIN_DOUBLE)
//        {
//            m_pScreenParam->m_fVpwAngle = 90.0f;
//        }
//        else
//        {
//            m_pScreenParam->m_fVpwAngle = atan(dZ / dY) * 180.0f / osg::PI;
//        }
//    }

    double dVpwPIAngle =  m_pScreenParam->m_fVpwAngle*osg::PI/180.0;
    m_pScreenParam->m_dVpwSin 	= sin(dVpwPIAngle);
    m_pScreenParam->m_dVpwCos 	= cos(dVpwPIAngle);
}

void COsgMainApp::Draw(int nCenterX, int nCenterY , double dScale, float fAngle,float fTile) {
    m_pScreenParam->m_nCenterX = nCenterX;
    m_pScreenParam->m_nCenterY = nCenterY;
    m_pScreenParam->m_fTilt    =  fTile;
    m_rpRoot->addChild(createNode());
    LoadModels(nCenterX, nCenterY, fAngle);
    TranslateMap(nCenterX, nCenterY, fAngle, fTile);
    m_Viewer->frame();
    m_rpRoot->removeChild(0, m_rpRootOsg->getNumChildren());
}


void COsgMainApp::LoadModels(int nCenterX, int nCenterY, float fAngle) {

    //轮廓面的半径进行屏幕换算
    double      radius  = 0.4;
    osg::ref_ptr<osgDB::Options>  rpOption = new osgDB::Options(std::string("noTriStripPolygons"));
    osg::ref_ptr<osg::Node>  pBuilding = osgDB::readNodeFile("/storage/emulated/0/cicv/OSG/BD/model/car/Model-Jianghuai-iEVS4-100k.obj", rpOption.get());
    LOGI("OnDrawCarModel getModel success ");
    //得到模型的包围盒
    osg::ComputeBoundsVisitor boundsVisitor;
    pBuilding->accept(boundsVisitor);
    osg::BoundingBox boundingBox = boundsVisitor.getBoundingBox();
    float modelRadius = MAX(boundingBox.xMax() - boundingBox.xMin(), boundingBox.yMax() - boundingBox.yMin());
    //取模型三个方向的最大值为模型半径
    modelRadius = MAX(modelRadius, boundingBox.zMax() - boundingBox.zMin()) / 2.0;
    const osg::BoundingSphere& bs       			= pBuilding->getBound();
    double size                                     = radius / modelRadius;
    //位置变换节点
    osg::ref_ptr<osg::MatrixTransform> positioned   = new osg::MatrixTransform;
    positioned->setDataVariance(osg::Object::STATIC);
    //模型对应的中心瓦片坐标转换为OSG坐标系
    double fX = (double)nCenterX;
    double fY = (double)nCenterY;
    CalNodeTexXY(m_pScreenParam, fX, fY);
    LOGI("TransCarModel ---  BS [%f,%f,%f], %f, [%f,%f,%f,%f,%f,%f],[%f,%f]",bs.center().x(), bs.center().y(), bs.center().z(), size,
         boundingBox.xMax(), boundingBox.xMin(), boundingBox.yMax(), boundingBox.yMin(), boundingBox.zMax(), boundingBox.zMin() ,fX, fY);

    float dZDeep = 0.0f;
    positioned->setMatrix(osg::Matrix::translate(-bs.center()) *
    osg::Matrix::rotate(osg::inDegrees(-90.0f), 1.0f, 0.0f, 0.0f) *
    osg::Matrix::rotate(osg::inDegrees( 90.0f), 0.0f, 1.0f, 0.0f) *
    osg::Matrix::scale(size, size, size) *
    osg::Matrix::translate(fX,(-boundingBox.zMin()+bs.center().z()+dZDeep)*size, fY));

    positioned->addChild(pBuilding);

    osg::Shader* pVertexShader    = new osg::Shader(osg::Shader::VERTEX,   gVertexShaderBeiDou);
    osg::Shader* pFragmentShader  = new osg::Shader(osg::Shader::FRAGMENT, gFragmentShaderBeiDou);
    osg::Program* pPipe           = new osg::Program;
    pPipe->addShader(pVertexShader);
    pPipe->addShader(pFragmentShader);
    positioned->getOrCreateStateSet()->setAttribute(pPipe);
    osg::ref_ptr<osg::Uniform> pSamUniformModel = new osg::Uniform(osg::Uniform::SAMPLER_2D, "sambuild");
    pSamUniformModel->set(0);
    positioned->getOrCreateStateSet()->addUniform(pSamUniformModel);


    m_rpRoot->addChild(positioned);
}

void COsgMainApp::TranslateMap(int centerX, int centerY, float angle,float fTile)
{
    //double fCenterX 				= (double)(2*(centerX-m_pScreenParam->m_nWndHeight/2)/(double)m_pScreenParam->m_nWndHeight - 1.0;
    //double fCenterY 				= (double)(2*centerY)/(double)m_pScreenParam->m_nWndHeight - 1.0;

    double dCenterX 				=(double)m_pScreenParam->m_fAspect * (1.0 - (double)centerX / (double)(m_pScreenParam->m_nWndWidth / 2.0));
    double dCenterY 				= 1.0 - (double)(2.0 * centerY) / (double)m_pScreenParam->m_nWndHeight;

    LOGI("RotateAngle--------------OSG RotateMap %f,%f, %f, [%f,%f] ,%f--[%.6f,%.6f,%.6f]", m_pScreenParam->m_fCullRatio, m_pScreenParam->m_fHdMapRatio, angle, dCenterX, dCenterY);

    m_rpPositioned->setDataVariance(osg::Object::STATIC);

    m_rpPositioned->setMatrix(
            osg::Matrixd::translate(osg::Vec3d(-dCenterX, 0.0, -dCenterY))
            * osg::Matrix::rotate(osg::inDegrees(-angle), 0.0, 1.0, 0.0)*osg::Matrix::rotate(osg::inDegrees(-fTile), 1.0, 0.0, 0.0)
            * osg::Matrix::translate(0.0, 0.0, m_pScreenParam->m_fCullRatio + m_pScreenParam->m_fHdMapRatio)
    );



    //m_rpRootOsg->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
}

//创建一个四边形节点
osg::ref_ptr<osg::Node> COsgMainApp::createNode() {

    //创建一个叶节点对象
    osg::ref_ptr<osg::Geode> geode =  new osg::Geode();
    //创建一个几何体对象
    osg::ref_ptr<osg::Geometry> geom =  new osg::Geometry();
    //添加顶点数据 注意顶点的添加顺序是逆时针
    osg::ref_ptr<osg::Vec3Array> v =  new osg::Vec3Array();
    //添加数据
    v->push_back(osg::Vec3( 0,  0,  0));
    v->push_back(osg::Vec3( 1.0,  0,  0));
    v->push_back(osg::Vec3( 1.0,  0,  1.0));
    v->push_back(osg::Vec3( 0,  0,  1.0));

    //设置顶点数据
    geom->setVertexArray(v.get());

    //创建纹理订点数据
    osg::ref_ptr<osg::Vec2Array> vt =  new osg::Vec2Array();
    //添加纹理坐标
    vt->push_back(osg::Vec2( 0,  0));
    vt->push_back(osg::Vec2( 1,  0));
    vt->push_back(osg::Vec2( 1,  1));
    vt->push_back(osg::Vec2( 0,  1));

    //设置纹理坐标
    geom->setTexCoordArray( 0, vt.get());

    //创建法线数组
    osg::ref_ptr<osg::Vec3Array> nc =  new osg::Vec3Array();
    //添加法线
    nc->push_back(osg::Vec3( 0, - 1,  0));
    //设置法线
    geom->setNormalArray(nc.get());
    //设置法绑定为全部顶点
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
    //添加图元
    geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::QUADS,  0,  4));

    //添加到叶子节点
    geode->addDrawable(geom.get());

    osg::Shader * vshader =  new osg::Shader(osg::Shader::VERTEX, gVertexShader);
    osg::Shader * fshader =  new osg::Shader(osg::Shader::FRAGMENT,
                                             gFragmentShader);

    osg::Program * prog =  new osg::Program;
    prog->addShader(vshader);
    prog->addShader(fshader);

    geode->getOrCreateStateSet()->setAttribute(prog);

    return geode.get();
}

/**
  * 瓦片坐标转换为OSG归一化坐标
  * param[in] pScreenParam                  Geom对象
  * param[in] dX                            瓦片坐标X
  * param[in] dY                            瓦片坐标Y
  * return                                  void
*/
void COsgMainApp::CalNodeTexXY(CScreenParam* pScreenParam, double& dX, double& dY)
{
    dX = (double)pScreenParam->m_fAspect * (1.0 - dX/(double)(pScreenParam->m_nWndWidth/2));
    dY = 1.0 - (2.0*(dY))/(double)pScreenParam->m_nWndHeight;
}
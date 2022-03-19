//
// Created by 龚喜 on 2022/3/19.
//

#include  "OsgMainApp.h"

OsgMainApp::OsgMainApp() {

}

void OsgMainApp::initOsgWindow( int x,  int y,  int width,  int height) {
    __android_log_write(ANDROID_LOG_ERROR,  "OSGANDROID",  "Init geometry");

    _viewer =  new osgViewer::Viewer();
    _viewer->setUpViewerAsEmbeddedInWindow(x, y, width, height);
    _viewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);

    _root =  new osg::Group();

    __android_log_write(ANDROID_LOG_ERROR,  "OSGANDROID",  "Init geometry 22");
    _viewer->realize();
    _viewer->addEventHandler( new osgViewer::StatsHandler);
    _viewer->addEventHandler(
            new osgGA::StateSetManipulator(
                    _viewer->getCamera()->getOrCreateStateSet()));
    _viewer->addEventHandler( new osgViewer::ThreadingHandler);
    _viewer->addEventHandler( new osgViewer::LODScaleHandler);

    _manipulator =  new osgGA::KeySwitchMatrixManipulator;
    _manipulator->addMatrixManipulator( '1',  "Trackball",
                                        new osgGA::TrackballManipulator());
    _viewer->setCameraManipulator(_manipulator.get());

    _viewer->getViewerStats()->collectStats( "scene",  true);


    loadModels();
}

void OsgMainApp::draw() {
    _viewer->frame();
}

void OsgMainApp::loadModels() {

    __android_log_write(ANDROID_LOG_ERROR,  "OSGANDROID",  "loadModelsccXXX2");

    osg::ref_ptr<osgDB::Options>  rpOption = new osgDB::Options(std::string("noTriStripPolygons"));

    osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile("/storage/emulated/0/cicv/OSG/BD/model/car/Model-Jianghuai-iEVS4-100k.obj", rpOption.get());
    __android_log_write(ANDROID_LOG_ERROR,  "OSGANDROID",  "loadModels 11");
    loadedModel->setName( "cow");
    if (loadedModel !=  NULL) {
        __android_log_print(ANDROID_LOG_ERROR,  "OSGANDROID",  "Not NULL");
    }

    osg::Shader* pVertexShader    = new osg::Shader(osg::Shader::VERTEX,   gVertexShaderBeiDou);
    osg::Shader* pFragmentShader  = new osg::Shader(osg::Shader::FRAGMENT, gFragmentShaderBeiDou);
    osg::Program* pPipe           = new osg::Program;
    pPipe->addShader(pVertexShader);
    pPipe->addShader(pFragmentShader);
    loadedModel->getOrCreateStateSet()->setAttribute(pPipe);
    osg::ref_ptr<osg::Uniform> pSamUniformModel = new osg::Uniform(osg::Uniform::SAMPLER_2D, "sambuild");
    pSamUniformModel->set(0);
    loadedModel->getOrCreateStateSet()->addUniform(pSamUniformModel);


    _root->addChild(loadedModel);


    osgViewer::Viewer::Windows windows;
    _viewer->getWindows(windows);
    for (osgViewer::Viewer::Windows::iterator itr = windows.begin();
         itr != windows.end(); ++itr) {
        (*itr)->getState()->setUseModelViewAndProjectionUniforms( true);
        (*itr)->getState()->setUseVertexAttributeAliasing( true);
    }

    _viewer->setSceneData( NULL);
    _viewer->setSceneData(_root.get());
    _manipulator->getNode();
    _viewer->home();

    _viewer->getDatabasePager()->clear();
    _viewer->getDatabasePager()->registerPagedLODs(_root.get());
    _viewer->getDatabasePager()->setUpThreads( 3,  1);
    _viewer->getDatabasePager()->setTargetMaximumNumberOfPageLOD( 2);
    _viewer->getDatabasePager()->setUnrefImageDataAfterApplyPolicy( true,  true);
}

//创建一个四边形节点
osg::ref_ptr<osg::Node> OsgMainApp::createNode() {

    //创建一个叶节点对象
    osg::ref_ptr<osg::Geode> geode =  new osg::Geode();
    //创建一个几何体对象
    osg::ref_ptr<osg::Geometry> geom =  new osg::Geometry();
    //添加顶点数据 注意顶点的添加顺序是逆时针
    osg::ref_ptr<osg::Vec3Array> v =  new osg::Vec3Array();
    //添加数据
    v->push_back(osg::Vec3( 0,  0,  0));
    v->push_back(osg::Vec3( 1,  0,  0));
    v->push_back(osg::Vec3( 1,  0,  1));
    v->push_back(osg::Vec3( 0,  0,  1));

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

    //创建颜色数组
    osg::ref_ptr<osg::Vec4Array> vc =  new osg::Vec4Array();
    //添加数据
    vc->push_back(osg::Vec4( 1,  0,  0,  1));
    vc->push_back(osg::Vec4( 0,  1,  0,  1));
    vc->push_back(osg::Vec4( 0,  0,  1,  1));
    vc->push_back(osg::Vec4( 1,  1,  0,  1));

    //设置颜色数组
    geom->setColorArray(vc.get());
    //设置颜色的绑定方式为单个顶点
    geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

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


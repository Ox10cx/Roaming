//
// Created by 龚喜 on 2022/3/19.
//

#ifndef ROAMING_OSGMAINAPP_H
#define ROAMING_OSGMAINAPP_H

#include "OsgHeaderFiles.h"

#define LOG_TAG  "OsgMainApp"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static  const  char gVertexShader[] =
        "void main() {                                                          \n"
        "    gl_Position  = gl_ModelViewProjectionMatrix * gl_Vertex;          \n"
        "}                                                                      \n";
static  const  char gFragmentShader[] =
        "void main() {                             \n"
        "  gl_FragColor =vec4(0.4,0.4,0.8,1.0);    \n"
        "}                                                                      \n";


static const char gVertexShaderBeiDou[] =
        "varying vec4 color;                                                    \n"
        "varying vec2 v_texCoord;                                         \n"
        "const vec3 lightPos      =vec3(0.0, 1.0, 0.0);                            \n"
        "const vec3 lightDir      =vec3(0, 0.0, -1.0);                            \n"
        "const vec4 cessnaColor   =vec4(1.0, 0.0, 0.0, 1.0);                    \n"
        "const vec4 lightAmbient  =vec4(1.0, 1.0, 1.0, 1.0);                    \n"
        "const vec4 lightDiffuse  =vec4(0.8, 0.75, 0.73, 1.0);                    \n"
        "const vec4 lightSpecular =vec4(0.8, 0.75, 0.73, 1.0);                    \n"
        "const vec4 matAmbient  =vec4(0.8, 0.75, 0.73, 1.0);                    \n"
        "const vec4 matDiffuse  =vec4(0.8, 0.75, 0.73, 1.0);                    \n"
        "const vec4 matSpecular =vec4(0.8, 0.75, 0.73, 1.0);                    \n"
        "void main() {                                                          \n"
        "    vec4 ambiCol = vec4(0.0);                                          \n"
        "    vec4 diffCol = vec4(0.0);                                          \n"
        "    vec4 specCol = vec4(0.0);                                          \n"
        "    gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;          \n"
        "    vec3 normal   = normalize(gl_NormalMatrix * gl_Normal);            \n"
        "    vec4 ecPos    = gl_ModelViewMatrix * gl_Vertex;                    \n"
        "    vec3 L        = normalize(lightPos-vec3(-ecPos.x, ecPos.yz));                     \n"
        "    color = matDiffuse * vec4(max(0.0, dot(normal, L))) + lightAmbient * 0.3;  \n"
        "    v_texCoord   = gl_MultiTexCoord0.xy;                        \n"
        "}                                                                      \n";


static const char gFragmentShaderBeiDou[] =
        "precision mediump float;                  \n"
        "varying mediump vec4 color;               \n"
        "varying  mediump vec2 v_texCoord;                      \n"
        "uniform sampler2D sambuild;                                \n"
        "void main() {                             \n"
        "    gl_FragColor = texture2D(sambuild, v_texCoord)*color;         \n"
        "}                                                             \n";




class COsgMainApp {
public:
    COsgMainApp();
    ~COsgMainApp();
    void InitOsgWindow(int width, int height, ModelViewMatrix initModelViewMatrix);
    void UpdateViewMatrix(ModelViewMatrix updateViewMatrix);
    void Draw(int nCenterX, int nCenterY , double dScale, float fAngle,float fTile);
private:
    void InitParameter(int width, int height, int model);
    /**
     * 初始化OsgRoot的节点
     */
    void InitOsgRoot();
    void SetCamera(ModelViewMatrix initModelViewMatrix);
    void LoadModels(int nCenterX, int nCenterY, float fAngle);
    void TranslateMap(int nCenterX, int nCenterY,float fAngle,float fTilt);
    osg::ref_ptr<osg::Node> createNode();
    void CalNodeTexXY(CScreenParam* pScreenParam, double& dX, double& dY);
private:
    osg::ref_ptr<osgViewer::Viewer>   m_Viewer;
    osg::ref_ptr<osg::Camera>         m_rpCamera;
    // 树最终节点
    osg::ref_ptr<osg::Group>          m_rpRootOsg;
    osg::ref_ptr<osg::MatrixTransform>  m_rpPositioned;
    // 当前场景的父节点
    osg::ref_ptr<osg::Group>          m_rpRoot;
    CScreenParam*                     m_pScreenParam;

};


#endif //ROAMING_OSGMAINAPP_H

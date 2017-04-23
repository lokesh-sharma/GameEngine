#include "RenderingEngine.h"

#include"ForwardAmbient.h"
#include"ForwardDirectional.h"
#include"ForwardPoint.h"
#include"ForwardSpot.h"
#include"display.h"
#include"CoreEngine.h"
#include"mesh.h"
#include"transform.h"
#include"FreeLook.h"

static Texture* g_temptarget = 0;
static Mesh * g_mesh = 0;
static Transform g_transform;
static Material* g_material;
static Camera* g_camera = 0;
static GameObject* g_cameraObject = 0;

RenderingEngine::RenderingEngine()
{
    //directionalShader = new ForwardDirectional("./res/forward-directional");
    ambientShader = new ForwardAmbient("./res/forward-ambient");
    //pointShader = new ForwardPoint("./res/forward-pointLight");
    //spotShader = new ForwardSpot("./res/forward-spotLight");
    //shader = new PhongShader("./res/phongShader");
    g_material = new Material();
    int width = 200;
    int height = 200;
    unsigned char * data = new unsigned char[width*height*4];
    memset(data , 0 , width*height*4);
    g_temptarget = new Texture( data , width , height , GL_LINEAR_MIPMAP_LINEAR , GL_COLOR_ATTACHMENT0);
    g_material->addTexture("diffuse" , g_temptarget);
//    g_material->addTexture("diffuse" , "./res/bricks.jpg");
//    g_material->addTexture("normal" , "./res/default_normal.jpg");
//    g_material->addTexture("dispMap" , "./res/default_disp.png");
    g_mesh = new Mesh("./res/plane.obj");
    g_camera = new FreeLook(glm::vec3(0.0f, 6.0f, 10.0f), 70.0f
    , 5.0/4.0, 0.1f, 100.0f);
    g_cameraObject = new GameObject();
    g_camera->setParent(g_cameraObject);
    //g_cameraObject->addComponent(g_camera);
    //g_camera->getTransform()->rotate()
}
RenderingEngine::~RenderingEngine()
{
    //dtor
}
void RenderingEngine::init(Display* d)
{
    display = d;
}
void RenderingEngine::render(GameObject* object)
{
    display->bindAsRenderTarget();
   // g_temptarget->bindAsRenderTarget();
    //glClearColor(0.1 , 0.1, 0.1, 1);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    object->render(*ambientShader , *camera , this);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE , GL_ONE);
    glDepthMask(false);
    glDepthFunc(GL_EQUAL);
   // object->render(*spotShader , *camera);
    for(int i = 0 ; i<point_lights.size(); i++)
    {
        active_point_light = point_lights[i];
        object->render(*(point_lights[i]->getShader()) , *camera , this);
    }
    for(int i = 0 ; i<dir_lights.size() ; i++)
    {
        active_dir_light = dir_lights[i];
        object->render(*(dir_lights[i]->getShader()) , *camera , this);
    }
    for(int i = 0 ; i<spot_lights.size() ; i++)
    {
        active_spot_light = spot_lights[i];
        object->render(*(spot_lights[i]->getShader()) , *camera , this);
    }
    glDepthFunc(GL_LESS);
    glDepthMask(true);
    glDisable(GL_BLEND);
    object->update();
//    display->bindAsRenderTarget();
//    glClearColor(0.1 , 0.1, 0.1, 1);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     g_temptarget->Bind(0);
//    ambientShader->Bind();
//    ambientShader->Update(g_transform , *g_camera  , *g_material , this);
//
//    //g_camera->update();
//    g_mesh->Draw();
   // glBindTexture(GL_TEXTURE_2D , 0);

}
 void RenderingEngine::addDirectionalLight(DirectionalLight* light)
 {
    dir_lights.push_back(light);
 }
  void RenderingEngine::addPointLight(PointLight* light)
 {
    point_lights.push_back(light);
 }
 void RenderingEngine::addSpotLight(SpotLight* light)
 {
    spot_lights.push_back(light);
 }

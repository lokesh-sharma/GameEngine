#include "RenderingEngine.h"

#include"ForwardAmbient.h"
#include"ForwardDirectional.h"
#include"ForwardPoint.h"
#include"ForwardSpot.h"
#include"display.h"
#include"CoreEngine.h"

RenderingEngine::RenderingEngine()
{
    //directionalShader = new ForwardDirectional("./res/forward-directional");
    ambientShader = new ForwardAmbient("./res/forward-ambient");
    //pointShader = new ForwardPoint("./res/forward-pointLight");
    //spotShader = new ForwardSpot("./res/forward-spotLight");
    //shader = new PhongShader("./res/phongShader");
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
    glDepthFunc(GL_LESS);
    glDepthMask(true);
    glDisable(GL_BLEND);
    object->update();
}
 void RenderingEngine::addDirectionalLight(DirectionalLight* light)
 {
    dir_lights.push_back(light);
 }
  void RenderingEngine::addPointLight(PointLight* light)
 {
    point_lights.push_back(light);
 }

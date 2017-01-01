#include "RenderingEngine.h"

#include"ForwardAmbient.h"
#include"ForwardDirectional.h"
#include"ForwardPoint.h"
#include"ForwardSpot.h"
RenderingEngine::RenderingEngine()
{
    directionalShader = new ForwardDirectional("./res/forward-directional");
    ambientShader = new ForwardAmbient("./res/forward-ambient");
    pointShader = new ForwardPoint("./res/forward-pointLight");
    spotShader = new ForwardSpot("./res/forward-spotLight");
    //shader = new PhongShader("./res/phongShader");
    camera = new Camera(glm::vec3(0.0f, 6.0f, 10.0f), 70.0f, (float)800/(float)600, 0.1f, 100.0f);
}
RenderingEngine::~RenderingEngine()
{
    //dtor
}
void RenderingEngine::render(GameObject* object)
{
    object->render(*ambientShader , *camera);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE , GL_ONE);
    glDepthMask(false);
    glDepthFunc(GL_EQUAL);
    object->render(*spotShader , *camera);
    glDepthFunc(GL_LESS);
    glDepthMask(true);
    glDisable(GL_BLEND);
    camera->update(TheInputHandler::getInstance()->getMousePos());
}

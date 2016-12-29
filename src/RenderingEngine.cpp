#include "RenderingEngine.h"

RenderingEngine::RenderingEngine()
{
    shader = new PhongShader("./res/phongShader");
    //shader = new PhongShader("./res/phongShader");
    camera = new Camera(glm::vec3(0.0f, 6.0f, 10.0f), 70.0f, (float)800/(float)600, 0.1f, 100.0f);
}
RenderingEngine::~RenderingEngine()
{
    //dtor
}

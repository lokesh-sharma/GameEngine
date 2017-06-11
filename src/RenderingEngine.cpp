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
#include"ShadowShader.h"
#include"SkyBoxManager.h"
#include"WaterRenderer.h"



RenderingEngine::RenderingEngine(Display* d)
{
    //directionalShader = new ForwardDirectional("./res/forward-directional");
    fogColor = glm::vec4(0.7,0.7,0.75,1.0);
    ambientShader = new ForwardAmbient("./res/Shaders/forward-ambient");
    dirShadowShader = new DirectionalShadowShader("./res/Shaders/directionalShadow");
    pointShadowShader = new PointShadowShader("./res/Shaders/pointShadow");
    depthShader = new Shader("./res/Shaders/depthShader");
    skyBoxManager = new SkyBoxManager();
    waterRenderer = new WaterRenderer();
    clipPlane = glm::vec4( 0 , -1 , 0 , 1000);
    //pointShader = new ForwardPoint("./res/forward-pointLight");
    //spotShader = new ForwardSpot("./res/forward-spotLight");
    //shader = new PhongShader("./res/phongShader");
    display = d;

    temptarget = new Texture(0 , GL_TEXTURE_2D, 1024 , 1024,GL_LINEAR , GL_DEPTH_COMPONENT16 ,
     GL_DEPTH_COMPONENT , true, GL_DEPTH_ATTACHMENT);
    pointshadowMap = new Texture(0 , GL_TEXTURE_CUBE_MAP , 1024 , 1024 , GL_LINEAR ,
     GL_DEPTH_COMPONENT , GL_DEPTH_COMPONENT , true, GL_DEPTH_ATTACHMENT);
     depthMap = new Texture(0 , GL_TEXTURE_2D, 1024 , 1024,GL_LINEAR , GL_DEPTH_COMPONENT16 ,
     GL_DEPTH_COMPONENT , true, GL_DEPTH_ATTACHMENT);

     //reflectionMap = new Texture("./res/bricks2.jpg");

    temp_material = new Material();
    temp_material->addTexture("diffuse" , temptarget);
    temp_material->setAmbientColor(glm::vec4(1 , 1 , 1 ,1.0));
    cameraObject1 = new GameObject();
    cameraObject2 = new GameObject();
    float aspectRatio  = display->getWidth()/display->getHeight();
    altCamera = new FreeLook(glm::vec3(0.0f, 0.0f, 4.2f), 70.0f,aspectRatio , 0.1f, 100.0f);
    tempCamera = new FreeLook(glm::vec3(0.0f, 0.0f, 4.2f), 70.0f,aspectRatio , 0.1f, 100.0f);

    altCamera->setParent(cameraObject1);
    tempCamera->setParent(cameraObject2);
    mesh = new Mesh("./res/Models/plane.obj");
    temp_transform.SetScale(glm::vec3(aspectRatio , 1 , 1));

}
RenderingEngine::~RenderingEngine()
{
     //dtor
}
void RenderingEngine::render(GameObject* object)
{

    glEnable(GL_CLIP_DISTANCE0);
    glm::vec3 cPos = camera->getPos();
    glm::quat cRot = camera->getRot();
    tempCamera->setProjection(camera->getProjection());
    tempCamera->getLocalTransform()->SetPos(cPos);
    tempCamera->getLocalTransform()->SetRot(cRot);

    glm::vec3 right = glm::normalize(cRot*glm::vec3(1,0,0));
    glm::vec3 euler = glm::eulerAngles(cRot);
    glm::quat newRot = glm::angleAxis(-2*euler.x, right);
    newRot = newRot*cRot;
    tempCamera->getLocalTransform()->SetRot(newRot);
    cPos.y = -cPos.y;
    tempCamera->getLocalTransform()->SetPos(cPos);
    renderDepthMap(object , camera , depthMap);
    clipPlane = glm::vec4( 0 , 1 , 0 , 0);
    renderScene(object , tempCamera, waterRenderer->getReflectionMap());
    clipPlane = glm::vec4( 0 , -1 , 0 , 0);
    renderScene(object , camera , waterRenderer->getRefractionMap());
    display->bindAsRenderTarget();
    glClearColor(0.1 , 0.1, 0.1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //ambientShader->Bind();
    //ambientShader->Update(temp_transform , *camera , *temp_material , this);
    //mesh->Draw();
    clipPlane = glm::vec4( 0 , -1 , 0 , 1000);
    renderScene(object , camera,scene);
    waterRenderer->render(*camera , this);
    //skyBoxManager->renderSkyBox(*camera , this);
    object->update();

}
void RenderingEngine::renderDepthMap(GameObject* object , Camera* mainCamera , Texture* target)
{
    target->bindAsRenderTarget();
    glClear(GL_DEPTH_BUFFER_BIT);
     object->render(*depthShader, *mainCamera , this);
}

void RenderingEngine::renderScene(GameObject* object , Camera* mainCamera , Texture* target )
{
    if(!target)
        display->bindAsRenderTarget();
    else
        target->bindAsRenderTarget();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    object->render(*ambientShader , *mainCamera , this);

    for(int i = 0 ; i<point_lights.size(); i++)
    {
        active_point_light = point_lights[i];
        ShadowInfo* shadowInfo = active_point_light->getShadowInfo();
        pointshadowMap->bindAsRenderTarget();
        glClear(GL_DEPTH_BUFFER_BIT);

        if(shadowInfo)
        {
            setShadowBias(active_point_light->getShadowInfo()->getBias());
            shadowTexelSize = glm::vec3(1.0f/1024.0f , 1.0f/1024.0f , 1.0f/1024.0f);
            //glEnable(GL_CULL_FACE);
             //glCullFace(GL_BACK);
            object->render(*pointShadowShader , *mainCamera ,this);

        }
        if(!target)
            display->bindAsRenderTarget();
        else
            target->bindAsRenderTarget();

        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE , GL_ONE);
        glDepthMask(false);
        glDepthFunc(GL_EQUAL);
        object->render(*(point_lights[i]->getShader()) , *mainCamera , this);
        glDepthFunc(GL_LESS);
        glDepthMask(true);
       glDisable(GL_BLEND);
    }
    for(int i = 0 ; i<dir_lights.size() ; i++)
    {
        active_dir_light = dir_lights[i];
        ShadowInfo* shadowInfo = dir_lights[i]->getShadowInfo();
        temptarget->bindAsRenderTarget();
        glClear(GL_DEPTH_BUFFER_BIT);

        if(shadowInfo )
        {
            altCamera->setProjection(shadowInfo->getProjection());
            glm::mat4 matrix = active_dir_light->getTransform()->getParentMatrix();

            glm::quat rotation = glm::quat_cast(matrix*glm::toMat4
            (active_dir_light->getTransform()->GetRot()));
            altCamera->getTransform()->SetRot(rotation);
            m_lightMatrix = altCamera->getMVP();
            setShadowBias(active_dir_light->getShadowInfo()->getBias());
            shadowTexelSize = glm::vec3(1.0f/1024.0f , 1.0f/1024.0f , 0.0f);
            glEnable(GL_CULL_FACE);
             glCullFace(GL_BACK);
            object->render(*dirShadowShader , *altCamera ,this);
            glDisable(GL_CULL_FACE);

        }
        if(!target)
            display->bindAsRenderTarget();
        else
            target->bindAsRenderTarget();

        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE , GL_ONE);
        glDepthMask(false);
        glDepthFunc(GL_EQUAL);

        object->render(*(dir_lights[i]->getShader()) , *mainCamera , this);

        glDepthFunc(GL_LESS);
        glDepthMask(true);
       glDisable(GL_BLEND);
    }
    for(int i = 0 ; i<spot_lights.size() ; i++)
    {
        active_spot_light = spot_lights[i];
        ShadowInfo* shadowInfo = spot_lights[i]->getShadowInfo();
        temptarget->bindAsRenderTarget();
        glClear(GL_DEPTH_BUFFER_BIT);
        if(shadowInfo)
        {
            altCamera->setProjection(shadowInfo->getProjection());

            glm::mat4 matrix = active_spot_light->getTransform()->getParentMatrix();
            glm::vec3 pos =active_spot_light->getTransform()->GetPos();

            glm::vec4 transformedPos = matrix*glm::vec4(pos.x , pos.y , pos.z , 1);
            altCamera->getTransform()->SetPos(glm::vec3(transformedPos.x , transformedPos.y , transformedPos.z));
            glm::quat rotation = glm::quat_cast(matrix*glm::toMat4
            (active_spot_light->getTransform()->GetRot()));
            altCamera->getTransform()->SetRot(rotation);

            m_lightMatrix = altCamera->getMVP();
            setShadowBias(active_spot_light->getShadowInfo()->getBias());
            shadowTexelSize = glm::vec3(1.0f/1024.0f , 1.0f/1024.0f , 0.0f);
            glEnable(GL_CULL_FACE);
             glCullFace(GL_BACK);
            object->render(*dirShadowShader , *altCamera ,this);
            glDisable(GL_CULL_FACE);

        }

        if(!target)
            display->bindAsRenderTarget();
        else
            target->bindAsRenderTarget();

        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE , GL_ONE);
        glDepthMask(false);
        glDepthFunc(GL_EQUAL);
        object->render(*(active_spot_light->getShader()) , *mainCamera , this);
        glDepthFunc(GL_LESS);
        glDepthMask(true);
       glDisable(GL_BLEND);
    }
     skyBoxManager->renderSkyBox(*mainCamera , this);


//    display->bindAsRenderTarget();
//    glClearColor(0.1 , 0.1, 0.1, 1);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     temptarget->Bind(0);
//    //g_temptarget->Bind(0);
//    ambientShader->Bind();
//    ambientShader->Update(temp_transform , *altCamera  , *temp_material , this);
//
   // altCamera->update();
    //mesh->Draw();
   // glBindTexture(GL_TEXTURE_2D , 0);

}
void RenderingEngine::addWaterTile(glm::vec3 pos , glm::vec3 scale)
{
    WaterRenderer::WaterQuad q = { pos , scale };
    waterRenderer->addWaterQuad(q);
}
void RenderingEngine::addSkyBox(std::string filename , std::string format)
{
    skyBoxManager->addSkyBox(filename , format);
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

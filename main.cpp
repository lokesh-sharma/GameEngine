#include <iostream>
#include <SDL2/SDL.h>
#include<math.h>
#include "./include/display.h"
#include "./include/mesh.h"
#include "./include/shader.h"
#include "./include/texture.h"
#include "./include/transform.h"
#include "./include/camera.h"
#include"./include/InputHandler.h"
#include"MeshRenderer.h"
#include"RenderingEngine.h"
#include"CoreEngine.h"
#include"GameObject.h"
#include"Game.h"
#include"Matrial.h"
#include"transform.h"
#include"BoundingSphere.h"
#include"AABB.h"
#include"Plane.h"
#include"PhysicsEngine.h"
#include"PhysicsEngineComponent.h"
#include"PhysicsObject.h"
#include"PhysicsObjectComponent.h"

int main(int argc, char** argv)
{
	Display display("OpenGL game Engine");
	GameObject* g1 = new GameObject;
    GameObject* g2 = new GameObject;
    GameObject* g3 = new GameObject;
    GameObject* g4 = new GameObject;
    GameObject* g5 = new GameObject;

    PhysicsEngine* pEngine = new PhysicsEngine;
    pEngine->addObject(new PhysicsObject( new BoundingSphere(glm::vec3(10,8,0),1.0f) , glm::vec3(-3,0,0)));
    pEngine->addObject(new PhysicsObject( new BoundingSphere(glm::vec3(-10,8,0),2.0f) , glm::vec3(1,0,0)));
    PhysicsEngineComponent* pComponent = new PhysicsEngineComponent(pEngine);
    g4->addComponent(new PhysicsObjectComponent(pEngine->getObject(0)));
    g5->addComponent(new PhysicsObjectComponent(pEngine->getObject(1)));

    Material* m = new Material();
    Material* m1 = new Material();
    m->addTexture("diffuse" , "./res/TextureAtlas.png");
    m1->addTexture("diffuse" , "./res/sphere.png");

    MeshRenderer f(new Mesh("./res/dima.obj"),m);
    MeshRenderer g(new Mesh("./res/sphere.obj"),m1);
    MeshRenderer h(new Mesh("./res/sphereBig.obj"),m1);
    Game* game = new Game();
    TheInputHandler::getInstance()->disableCursor();

    TheInputHandler::getInstance()->setDisplay(&display);

    CoreEngine core(&display , game , new RenderingEngine() );
     g1->getTransform()->SetPos(glm::vec3(0,2,0));
    g2->getTransform()->SetPos(glm::vec3(0,-1,0));

    g1->addComponent(&f);
    game->addToScene(g1);
    game->addToScene(g2);
    game->addToScene(g3);
    game->addToScene(g4);
    game->addToScene(g5);

    //g2->addComponent(&g);
    game->setEngine(&core);
    //SpotLight*sp = new SpotLight(glm::vec3(1,1,1) , 2.0f);
    g3->addComponent(new SpotLight(glm::vec3(1,1,1) , 3.0f ));
      g2->addComponent(new Camera(glm::vec3(0.0f, 6.0f, 10.0f), 70.0f
    , (float)display.getWidth()/(float)display.getHeight(), 0.1f, 100.0f));
    g4->addComponent(&g);
    g5->addComponent(&h);

    core.start();
	float counter = 0.0f;
    long framestart;
    g3->getTransform()->SetPos(glm::vec3(0,4,0));
    g4->getTransform()->SetPos(glm::vec3(10,8,0));
    g5->getTransform()->SetPos(glm::vec3(-10,8,0));
	while(core.is_running())
	{
        framestart = SDL_GetTicks();
        pEngine->simulate(0.1f);
        pEngine->handleCollisions();
        core.run();

		TheInputHandler::getInstance()->resetStates();
		long time = SDL_GetTicks() - framestart;
		std::cout<<1000.0/time<<std::endl;
		counter += 0.1;
	}

	return 0;
}

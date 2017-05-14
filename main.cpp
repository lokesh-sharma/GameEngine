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
#include"FreeLook.h"
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
#include"ForwardAmbient.h"
#include"Player.h"
#include"FPSCamera.h"



int main(int argc, char** argv)
{

	Display display("OpenGL game Engine");
	GameObject* g1 = new GameObject;
    GameObject* g2 = new GameObject;
    GameObject* g3 = new GameObject;
    GameObject* g4 = new GameObject;
    GameObject* g5 = new GameObject;
    GameObject* g6 = new GameObject;

    Mesh* mesh1 = new Mesh("./res/plane2.obj");
    Mesh* mesh2 = new Mesh("./res/sphere2.obj");
    Mesh* mesh3 = new Mesh("./res/cube4.obj");

    PhysicsEngine* pEngine = new PhysicsEngine();
    pEngine->addObject(new PhysicsObject(mesh1 , glm::vec3(0,0,0) , 0 , 1) , "dima");
    pEngine->addObject(new PhysicsObject(glm::vec3(0,10,1) ,glm::vec3(2,2,2) ,
     5 , PhysicsObject::TYPE_BOUNDINGSPHERE) , "sphere");
    pEngine->addObject(new PhysicsObject(glm::vec3(1,4,0) , glm::vec3(2,2,2) , 2 ,
    PhysicsObject::TYPE_BOX) , "cube");

    PhysicsObjectComponent* comp = new PhysicsObjectComponent(pEngine->getObject("dima"));
    PhysicsObjectComponent* comp2 = new PhysicsObjectComponent(pEngine->getObject("sphere"));
    PhysicsObjectComponent* comp3 = new PhysicsObjectComponent(pEngine->getObject("cube"));
    //PhysicsObjectComponent* comp3 = new PhysicsObjectComponent(pEngine->getObject("cube"));
//    btTransform qt;
//    qt = pEngine->getObject("cube")->getRigidBody()->getWorldTransform();
//    qt.setRotation(btQuaternion(1,0,0,0));
//    pEngine->getObject("cube")->getRigidBody()->setWorldTransform(qt);

    Material* m = new Material();
    Material* m1 = new Material();
    m->addTexture("diffuse" , "./res/bricks2.jpg");
    m->addTexture("normal" , "./res/bricks2_normal.png");
    m->addTexture("dispMap" , "./res/bricks2_disp.jpg");
    m1->addTexture("diffuse" , "./res/1diffuse.jpg");
    m1->addTexture("normal" , "./res/1normal.jpg");
    m1->addTexture("dispMap" , "./res/1disp.jpg");
    GameComponent* player = new Player(pEngine);

    MeshRenderer f( mesh1,m1);
    MeshRenderer g( mesh2,m);
    MeshRenderer h( mesh3,m);

    Game* game = new Game();
    TheInputHandler::getInstance()->disableCursor();

    TheInputHandler::getInstance()->setDisplay(&display);
    RenderingEngine* renderer = new RenderingEngine(&display);

    CoreEngine core(&display , game , renderer );
    renderer->setCoreEngine(&core);
//     g1->getTransform()->SetPos(glm::vec3(0,2,0));
//    g2->getTransform()->SetPos(glm::vec3(0,-1,0));

    g1->addComponent(&f);
    g1->addComponent(comp);

    game->addToScene(g1);
    game->addToScene(g2);
    game->addToScene(g3);
    game->addToScene(g4);
    game->addToScene(g5);

    //g2->addComponent(&g);
    game->setEngine(&core);
    //SpotLight*sp = new SpotLight(glm::vec3(1,1,1) , 2.0f);
    PointLight*point = new PointLight(glm::vec3(1,1,1) , 10.0f);
    DirectionalLight * dir =new DirectionalLight(glm::vec3(1,1  ,1) , 1.0f);
    g3->addComponent(dir);

    g3->getTransform()->rotate(glm::vec3(1,0,0) , -45);
      g2->addComponent(new FreeLook(glm::vec3(0.0f, 6.0f, 10.0f), 70.0f
    , (float)display.getWidth()/(float)display.getHeight(), 0.1f, 100.0f));
    g4->addComponent(&g);
    g4->addComponent(comp2);
      //g2->addComponent(player); //order is important

    g5->addComponent(&h);
    g5->addComponent(comp3);
    core.start();
	float counter = 0.0f;
    long framestart;
    g3->getTransform()->SetPos(glm::vec3(0,3,0));

	while(core.is_running())
	{
//        glMatrixMode(GL_PROJECTION);
//glLoadIdentity();
//glOrtho(0, display.getWidth(), display.getHeight(), 0, -1, 1);

        framestart = SDL_GetTicks();
        core.run();
        pEngine->simulate(1/60.0);
        pEngine->handleCollisions();


		TheInputHandler::getInstance()->resetStates();
		long time = SDL_GetTicks() - framestart;



		//std::cout<<1000.0/time<<std::endl;
		counter += 0.1;
		//dir->setIntensity((glm::sin(counter) + 1)*3);
	}

	return 0;
}


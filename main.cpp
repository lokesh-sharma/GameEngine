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
#include"GUIManager.h"
#include"ObjLoader.h"



int main(int argc, char** argv)
{

	Display display("OpenGL game Engine");
	GameObject* baseTerrain = new GameObject;
    GameObject* g2 = new GameObject;
    GameObject* g3 = new GameObject;
    GameObject* g4 = new GameObject;


    Mesh* terrainMesh = new Mesh("./res/terrain2.obj");
    //Mesh* mesh2 = new Mesh("./res/sphere2.obj");
    Mesh* mesh3 = new Mesh("./res/cube.obj");
//    std::vector<glm::vec3> verts;
//    std::vector<glm::vec2> uvs;
//    std::vector<glm::vec3> normals;
//    ObjLoader* o1 = new ObjLoader("./res/cubetest.obj" ,verts , uvs , normals );
//    std::cout<<verts.size()<<" "<<uvs.size()<<" "<<normals.size()<<std::endl;

    PhysicsEngine* pEngine = new PhysicsEngine();
    pEngine->addObject(new PhysicsObject(terrainMesh , glm::vec3(0,0,0) , 0 , 1) , "terrain");
   // pEngine->addObject(new PhysicsObject(glm::vec3(0,10,1) ,glm::vec3(2,2,2) ,
    // 5 , PhysicsObject::TYPE_BOUNDINGSPHERE) , "sphere");
    pEngine->addObject(new PhysicsObject(glm::vec3(20,25,0) , glm::vec3(2,2,2) , 2 ,
    PhysicsObject::TYPE_BOX) , "cube");

    PhysicsObjectComponent* terrainCollider = new PhysicsObjectComponent(pEngine->getObject("terrain"));
   // PhysicsObjectComponent* comp2 = new PhysicsObjectComponent(pEngine->getObject("sphere"));
    PhysicsObjectComponent* comp3 = new PhysicsObjectComponent(pEngine->getObject("cube"));
    //PhysicsObjectComponent* comp3 = new PhysicsObjectComponent(pEngine->getObject("cube"));
//    btTransform qt;
//    qt = pEngine->getObject("cube")->getRigidBody()->getWorldTransform();
//    qt.setRotation(btQuaternion(1,0,0,0));
//    pEngine->getObject("cube")->getRigidBody()->setWorldTransform(qt);

   Material* m = new Material();
    Material* terrainTexture = new Material();
    //Material* m2 = new Material();
    m->addTexture("diffuse" , "./res/bricks2.jpg");
    m->addTexture("normal" , "./res/bricks2_normal.jpg");
    m->addTexture("dispMap" , "./res/bricks2_disp.jpg");
    terrainTexture->addTexture("diffuse" , "./res/grass.jpg");
    terrainTexture->addTexture("normal" , "./res/default_normal.jpg");
    terrainTexture->addTexture("dispMap" , "./res/default_disp.png");
    //m2->addTexture("diffuse" , "./res/leaf.png");
   // m2->addTexture("normal" , "./res/default_normal.jpg");
    //m2->addTexture("dispMap" , "./res/default_disp.png");
    GameComponent* player = new Player(pEngine);

    MeshRenderer f( terrainMesh,terrainTexture);
    MeshRenderer g( mesh3,m);

    Game* game = new Game();
    TheInputHandler::getInstance()->disableCursor();

    TheInputHandler::getInstance()->setDisplay(&display);
    RenderingEngine* renderer = new RenderingEngine(&display);
    GUIManager * manager =   new GUIManager(display.getWidth()/display.getHeight());

    manager->addGUI("./res/crosshair.png" , glm::vec3(0,0,0) , glm::vec3(0.03,0.03,1));
    renderer->addSkyBox("./res/skybox" , "png");

    renderer->addWaterTile(glm::vec3( 50 , 0 , 0) , glm::vec3(100 , 100 , 100));

    CoreEngine core(&display , game , renderer , manager);
    renderer->setCoreEngine(&core);
//     g1->getTransform()->SetPos(glm::vec3(0,2,0));
//    g2->getTransform()->SetPos(glm::vec3(0,-1,0));

    baseTerrain->addComponent(&f);
    baseTerrain->addComponent(terrainCollider);

    game->addToScene(baseTerrain);
    game->addToScene(g2);
    game->addToScene(g3);
    game->addToScene(g4);

    //g2->addComponent(&g);
    game->setEngine(&core);
    //SpotLight*sp = new SpotLight(glm::vec3(1,1,1) , 2.0f);
    PointLight*point = new PointLight(glm::vec3(1,1,1) , 10.0f);
    DirectionalLight * dir =new DirectionalLight(glm::vec3(1,1  ,1) , 1.3f);
    SpotLight * spot =new SpotLight(glm::vec3(1,1  ,1) , 12.0f);
    g3->addComponent(dir);
   // g4->addComponent(comp3);
    g4->addComponent(&g);
    g4->getTransform()->SetPos(glm::vec3(10 , 2 , 0));
    g4->getTransform()->SetScale(glm::vec3(2 , 2, 2));

      g2->addComponent(new FreeLook(glm::vec3(0.0f, 6.0f, 10.0f), 70.0f
    , (float)display.getWidth()/(float)display.getHeight(), 0.1f, 1000.0f));
    //g4->addComponent(&g);
    //g4->addComponent(comp2);
    //g2->addComponent(player); //order is important

    //g5->addComponent(&h);
    //g5->addComponent(comp3);
    //g6->addComponent(&i);
//    g6->addComponent(&i);
//    g7->addComponent(&j);
//    g8->addComponent(&k);
//    g9->addComponent(&l);
//    g10->addComponent(&m);
//    g11->addComponent(&n);
    const float offset = 88.35;
    core.start();
	float counter = 0.0f;
    long framestart;
    g3->getTransform()->SetPos(glm::vec3(0,4,0));
    g3->getTransform()->rotate(glm::vec3(1,0,0) , -45);
    g3->getTransform()->rotate(glm::vec3(0,1,0) , 90 + 45);

    //g6->getTransform()->rotate(glm::vec3(1,0,0) , 90);
	while(core.is_running())
	{
//        glMatrixMode(GL_PROJECTION);
//glLoadIdentity();
//glOrtho(0, display.getWidth(), display.getHeight(), 0, -1, 1);

        core.run();
        pEngine->simulate(1/60.0);
        pEngine->handleCollisions();


		TheInputHandler::getInstance()->resetStates();
        //g3->getTransform()->rotate(glm::vec3(1,0,0) , (glm::sin(counter)+1)*10);


		//std::cout<<1000.0/time<<std::endl;
		counter += 0.1;
		//dir->setIntensity((glm::sin(counter) + 1)*3);
	}

	return 0;
}


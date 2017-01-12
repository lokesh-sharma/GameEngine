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

const int DISPLAY_WIDTH = 1152;
const int DISPLAY_HEIGHT = 800;

//const int DISPLAY_WIDTH = 800;
//const int DISPLAY_HEIGHT = 600;

int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

    GameObject* g1 = new GameObject;
    GameObject* g2 = new GameObject;
    GameObject* g3 = new GameObject;
    Material* m = new Material();
    Material* m1 = new Material();
     m1->addTexture("diffuse" , "./res/sphere.png");
    m->addTexture("diffuse" , "./res/TextureAtlas.png");

    MeshRenderer f(new Mesh("./res/dima.obj"),m);
    MeshRenderer g(new Mesh("./res/Buddha.obj"),m1);

    Game* game = new Game();
    TheInputHandler::getInstance()->disableCursor();

    Shader* s = new PhongShader("./res/phongShader");
    TheInputHandler::getInstance()->setDisplay(&display);

    CoreEngine core(&display , game , new RenderingEngine() );
     g1->getTransform()->SetPos(glm::vec3(0,2,0));
    g2->getTransform()->SetPos(glm::vec3(0,-1,0));

    g1->addComponent(&f);
    game->addToScene(g1);
    game->addToScene(g2);
    game->addToScene(g3);

    //g2->addComponent(&g);
    game->setEngine(&core);
    g1->addComponent(new PointLight(glm::vec3(1,1,1) , 6.0f , glm::vec3(0,5,2)));
      g2->addComponent(new Camera(glm::vec3(0.0f, 6.0f, 10.0f), 70.0f
    , (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.1f, 100.0f));

    core.start();
	float counter = 0.0f;
    long framestart;
	while(core.is_running())
	{
        framestart = SDL_GetTicks();
        g2->getTransform()->rotate(glm::vec3(0,1,0) , 0.1);
        core.run();

		TheInputHandler::getInstance()->resetStates();
		long time = SDL_GetTicks() - framestart;
		std::cout<<1000.0/time<<std::endl;
		counter += 1;
	}

	return 0;
}

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

const int DISPLAY_WIDTH = 800;
const int DISPLAY_HEIGHT = 600;

int main(int argc, char** argv)
{
    /*glm::quat q = glm::angleAxis(-90.0f , glm::vec3(1.0f , 0.0f , 0.0f));
    glm::vec3 up  = q*glm::vec3(0,0,-1);
    std::cout<<up.x<<" "<<up.y<<" "<<up.z<<std::endl;*/
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	Mesh monkey("./res/Buddha.obj");
	Mesh monkey2("./res/plane.obj");

    GameObject* g1 = new GameObject;
    Material* m = new Material();
    m->addTexture("diffuse" , "./res/TextureAtlas.png");
    MeshRenderer f(new Mesh("./res/dima.obj"),m);
   // BaseLight*b = new PointLight(glm::vec3(1,1,0) , 6.0f , glm::vec3(0,2,0));
    Game* game = new Game();
    //game->addToScene(g1);

    Shader* s = new PhongShader("./res/phongShader");
    TheInputHandler::getInstance()->setDisplay(&display);
    TheInputHandler::getInstance()->disableCursor();
    CoreEngine core(&display , game , new RenderingEngine() );
    g1->addComponent(&f);
    game->addToScene(g1);
    game->setEngine(&core);
    g1->addComponent(new PointLight(glm::vec3(1,1,0) , 6.0f , glm::vec3(0,2,0)));
    //g1->addComponent(new DirectionalLight(glm::vec3(1,0,0) , 6.0f));
    g1->addComponent(new DirectionalLight(glm::vec3(0,0,1) , 6.0f));
    core.start();
	float counter = 0.0f;
    long framestart;
	while(core.is_running())
	{
        framestart = SDL_GetTicks();

        core.run();

		TheInputHandler::getInstance()->resetStates();
		long time = SDL_GetTicks() - framestart;
		std::cout<<1000.0/time<<std::endl;
		counter += 0.001;
	}

	return 0;
}

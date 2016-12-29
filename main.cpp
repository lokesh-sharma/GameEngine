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

const int DISPLAY_WIDTH = 800;
const int DISPLAY_HEIGHT = 600;

int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	Mesh monkey("./res/Buddha.obj");
	Mesh monkey2("./res/plane.obj");


    GameObject* g1 = new GameObject;
    Material* m = new Material();
    m->addTexture("diffuse" , "./res/sphere.png");
    g1->addComponent(new MeshRenderer(new Mesh("./res/Buddha.obj"),m));
    Game* game = new Game();
    game->addToScene(g1);

    Shader* s = new PhongShader("./res/phongShader");
    CoreEngine core(&display , game , new RenderingEngine() );
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

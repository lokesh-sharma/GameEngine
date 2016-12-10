#include <iostream>
#include <SDL2/SDL.h>
#include "./include/display.h"
#include "./include/mesh.h"
#include "./include/shader.h"
#include "./include/texture.h"
#include "./include/transform.h"
#include "./include/camera.h"
#include"./include/InputHandler.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	Mesh monkey("./res/Buddha.obj");

	Shader shader("./res/basicShader");
	Texture tex("./res/sphere.png");
	Transform transform;
	Camera camera(glm::vec3(0.0f, 4.0f, -10.0f), 70.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.1f, 100.0f);

	float counter = 0.0f;
    long framestart;
	while(display.isRunning())
	{
        framestart = SDL_GetTicks();
		//display.Clear(0.3f, 0.3f, 0.3f, 1.0f);
		display.Clear(0.0f, 0.0f, 0.0f, 1.0f);

		glm::vec3 pos = camera.getPos();
		shader.setUniformVector3f("eyePos" , pos.x , pos.y , -pos.z);

		shader.Bind();
        tex.Bind();
        monkey.Draw();

		shader.Update(transform, camera);
		display.update(transform);

		display.SwapBuffers();

		TheInputHandler::getInstance()->resetStates();
		long time = SDL_GetTicks() - framestart;
		std::cout<<1000.0/time<<std::endl;
	}

	return 0;
}

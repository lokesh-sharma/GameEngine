#include <iostream>
#include <SDL2/SDL.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include"InputHandler.h"
#include"trackball.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	Mesh monkey("./res/sphere.obj");

	Shader shader("./res/basicShader");
	Texture texture1("./res/floor.png");
	Texture tex("./res/floor.png");
	Transform transform;
	Camera camera(glm::vec3(0.0f, 4.0f, -10.0f), 70.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.1f, 100.0f);
    TrackBall track(glm::vec3(0.0001f, 5.0f, -10.0f), 70.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.1f, 100.0f);
	float counter = 0.0f;
    long framestart;
	while(display.isRunning())
	{
        framestart = SDL_GetTicks();
		//display.Clear(0.3f, 0.3f, 0.3f, 1.0f);
		display.Clear(0.0f, 0.0f, 0.0f, 1.0f);

		glm::vec3 pos = camera.getPos();
		shader.setUniform(3 , pos.x , pos.y , -pos.z);

		shader.Bind();
        tex.Bind();
        monkey.Draw();

		shader.Update(transform, camera);
		display.update(transform);

		display.SwapBuffers();

		//counter += 0.01f;
		TheInputHandler::getInstance()->resetStates();
		long time = SDL_GetTicks() - framestart;
		std::cout<<1000.0/time<<std::endl;
	}

	return 0;
}

#include "../include/display.h"
#include <GL/glew.h>
#include <iostream>
#include"../include/InputHandler.h"
#include"../include/transform.h"

Display::Display(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
       //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);
    m_running = true;
	GLenum res = glewInit();
    if(res != GLEW_OK)
    {
		std::cerr << "Glew failed to initialize!" << std::endl;
    }

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
}

void Display::clean()
{
    m_running = false;
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::SwapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}
void Display::update(Transform& t)
{
    TheInputHandler::getInstance()->update(*this);

    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_ESCAPE))
        clean();

    if(TheInputHandler::getInstance()->getMouseWheelState(UP))
    {
        t.GetPos().z -= 1;
    }
    if(TheInputHandler::getInstance()->getMouseWheelState(DOWN))
    {
        t.GetPos().z += 1;
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_RIGHT))
    {
        t.GetRot().y += 10;
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_LEFT))
    {
        t.GetRot().y -= 10;
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_D))
    {
        t.GetPos().x += 1;
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_A))
    {
        t.GetPos().x -= 1;
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_UP))
    {
        t.GetPos().y -= 0.5;
    }
    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_DOWN))
    {
        t.GetPos().y += 0.5;
    }
}


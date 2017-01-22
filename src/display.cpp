#include "../include/display.h"
#include <GL/glew.h>
#include <iostream>
#include"../include/InputHandler.h"
#include"../include/transform.h"

Display::Display( const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_DisplayMode current;
    int x = SDL_GetCurrentDisplayMode(0 , &current);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
       //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

    m_width = current.w;
    m_height = current.h;

    if(x == 0)
        m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, current.w, current.h, SDL_WINDOW_OPENGL);
	else
        std::cerr<<"Error in getting display information\n";
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
void Display::update()
{
    TheInputHandler::getInstance()->update(*this);

    if(TheInputHandler::getInstance()->isKeyDown(SDL_SCANCODE_ESCAPE))
        clean();

}


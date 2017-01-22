#ifndef DISPLAY_INCLUDED_H
#define DISPLAY_INCLUDED_H

#include <string>
#include <SDL2/SDL.h>
#include"camera.h"
#include"transform.h"

class Display
{
public:
	Display(const std::string& title);

	int getWidth()const { return m_width;}
	int getHeight()const { return m_height;}

	void Clear(float r, float g, float b, float a);
	void SwapBuffers();
	void update();
    void clean();
    bool isRunning() { return m_running;}
    SDL_Window* getWindow() { return m_window;}
protected:
private:
	void operator=(const Display& display) {}
	Display(const Display& display) {}
	bool m_running;
	int m_width;
	int m_height;

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
};

#endif

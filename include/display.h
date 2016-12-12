#ifndef DISPLAY_INCLUDED_H
#define DISPLAY_INCLUDED_H

#include <string>
#include <SDL2/SDL.h>
#include"camera.h"
#include"transform.h"

class Display
{
public:
	Display(int width, int height, const std::string& title);

	void Clear(float r, float g, float b, float a);
	void SwapBuffers();
	void update(Camera& c);
    void clean();
    bool isRunning() { return m_running;}
protected:
private:
	void operator=(const Display& display) {}
	Display(const Display& display) {}
	bool m_running;

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
};

#endif

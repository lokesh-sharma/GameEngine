#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include<SDL2/SDL.h>
#include<vector>
#include<glm/glm.hpp>

class Display;

enum mouse_buttons
{
    LEFT=0,
    MIDDLE=1,
    RIGHT=2
};
enum mouse_scroll
{
    UP=0,
    DOWN=1
};
class InputHandler
{
private:
    static InputHandler* pInstance;
    const Uint8* m_keystate;
    std::vector<bool>m_mouseButtonStates;
    std::vector<bool>m_mouseWheelStates;
    glm::vec2 m_mousePos;
    Display* display;
    InputHandler() : m_keystate(NULL) ,m_mousePos( glm::vec2(0,0))
    {
        for(int i = 0 ; i<3 ; i++)
            m_mouseButtonStates.push_back(false);
        for(int i = 0 ; i<2 ; i++)
            m_mouseWheelStates.push_back(false);
    }
    void onKeyDown();
    void onKeyUp();

    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);
    void onMouseWheel(SDL_Event& event);
    void onDrag(SDL_Event& event);
public:
    static InputHandler* getInstance()
    {
        if(pInstance==0)
        {
            pInstance = new InputHandler();
            return pInstance;
        }
        else return pInstance;
    }
    void update(Display& d);

    bool isKeyDown(SDL_Scancode key);
    void clean() {};
    bool getMouseButtonState(int button)
     { return m_mouseButtonStates[button];}
    void resetStates()
    {
        m_mouseWheelStates[UP]=m_mouseWheelStates[DOWN]=0;
        m_mouseButtonStates[LEFT] = 0;
        m_mouseButtonStates[MIDDLE] = 0;
        m_mouseButtonStates[RIGHT] = 0;
    }
    void setDisplay(Display*d) { display = d;}
    void setMousePos(int x , int y);
    void disableCursor() {SDL_ShowCursor(SDL_DISABLE);}
    bool getMouseWheelState(int motion)
    {
        return m_mouseWheelStates[motion];
    }
    glm::vec2 getMousePos() { return m_mousePos;}
    Display*getDisplay() { return display ;}

};
typedef InputHandler TheInputHandler;
#endif // INPUTHANDLER_

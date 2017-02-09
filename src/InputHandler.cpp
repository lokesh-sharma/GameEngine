#include "../include/InputHandler.h"
#include"../include/display.h"
#include<iostream>

InputHandler* InputHandler::pInstance = 0;

void InputHandler::update(Display&d)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            d.clean();
            break;
        case SDL_MOUSEWHEEL:
            onMouseWheel(event);
            break;
        case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event);
            break;
        case SDL_MOUSEMOTION:
            onMouseMove(event);
        case SDL_KEYDOWN:
            onKeyDown();
            break;
        case SDL_KEYUP:{
            onKeyUp();
            break;
            }

        default : break;
        }
    }

}
bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if(m_keystate!= 0)
    {
        if(m_keystate[key]==1)
            return true;
        else return false;
    }
    return false;
}
void InputHandler::onKeyDown()
{
     m_keystate = SDL_GetKeyboardState(0);
     if(isKeyDown(SDL_SCANCODE_W))
       m_movementKeysStates[W_KEY] = 1;
    if(isKeyDown(SDL_SCANCODE_A))
       m_movementKeysStates[A_KEY] = 1;
    if(isKeyDown(SDL_SCANCODE_S))
       m_movementKeysStates[S_KEY] = 1;
    if(isKeyDown(SDL_SCANCODE_D))
       m_movementKeysStates[D_KEY] = 1;
}
void InputHandler::onKeyUp()
{
     m_keystate = SDL_GetKeyboardState(0);
}
void InputHandler::onMouseButtonDown(SDL_Event& event)
{
        if(event.button.button==SDL_BUTTON_LEFT)
                m_mouseButtonStates[LEFT]=true;
        if(event.button.button==SDL_BUTTON_RIGHT)
                m_mouseButtonStates[RIGHT]=true;
        if(event.button.button==SDL_BUTTON_MIDDLE)
                m_mouseButtonStates[MIDDLE]=true;

}
void InputHandler::onMouseButtonUp(SDL_Event& event)
{
        if(event.button.button==SDL_BUTTON_LEFT)
                m_mouseButtonStates[LEFT]=false;
        if(event.button.button==SDL_BUTTON_RIGHT)
                m_mouseButtonStates[RIGHT]=false;
        if(event.button.button==SDL_BUTTON_MIDDLE)
                m_mouseButtonStates[MIDDLE]=false;
}
void InputHandler::onMouseWheel(SDL_Event& event)
{
    if(event.wheel.y < 0)
        m_mouseWheelStates[DOWN] = 1;
    else
        m_mouseWheelStates[UP] = 1;
}
void InputHandler::onMouseMove(SDL_Event& event)
{
    m_mousePos.x = event.motion.x;
    m_mousePos.y = event.motion.y;
}
void InputHandler::setMousePos(int x , int y)
{
    SDL_WarpMouseInWindow(display->getWindow() , x , y);
}

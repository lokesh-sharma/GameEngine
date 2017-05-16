#ifndef COREENGINE_H
#define COREENGINE_H


#include"Game.h"
#include"RenderingEngine.h"
#include"display.h"
#include<GL/glew.h>
#include<GL/gl.h>

class GUIManager;


class CoreEngine
{
public:
    CoreEngine( Display* display , Game* game , RenderingEngine* renderingEngine , GUIManager* m);
    void start(){ m_running = true;}
    void stop() { m_running = false;}
    Display* getDisplay() { return m_display;}
    void run();
    bool is_running() { return m_running;}
    RenderingEngine* getRenderingEngine() { return renderingEngine;}
    virtual ~CoreEngine();
private:
    bool m_running;
    RenderingEngine* renderingEngine;
    GUIManager* m_guiManager;
    Display* m_display;
    Game* m_game;
    CoreEngine(const CoreEngine& other) {}
    CoreEngine& operator=(const CoreEngine& other) {}
};

#endif // COREENGINE_H

#ifndef COREENGINE_H
#define COREENGINE_H


#include"Game.h"
#include"RenderingEngine.h"
#include"display.h"
#include<GL/glew.h>
#include<GL/gl.h>

class GUIManager;
class PostProcess;


class CoreEngine
{
public:
    CoreEngine( Display* display , Game* game , RenderingEngine* renderingEngine , GUIManager* m);

    void start(){ m_running = true;}
    void stop() { m_running = false;}
    void run();
    bool is_running() { return m_running;}

    Display* getDisplay() { return m_display;}
    float getDeltaTime() { return m_deltaTime;}
    RenderingEngine* getRenderingEngine() { return renderingEngine;}
    PostProcess* getPostProcessManager() { return m_postProcessManager;}

    virtual ~CoreEngine();
private:
    bool m_running;
    float m_deltaTime;
    RenderingEngine* renderingEngine;
    GUIManager* m_guiManager;
    PostProcess* m_postProcessManager;
    Display* m_display;
    Game* m_game;
    CoreEngine(const CoreEngine& other) {}
    CoreEngine& operator=(const CoreEngine& other) {}
};

#endif // COREENGINE_H

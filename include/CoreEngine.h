#ifndef COREENGINE_H
#define COREENGINE_H


#include"Game.h"
#include"RenderingEngine.h"
#include"display.h"


class CoreEngine
{
public:
    CoreEngine( Display* display , Game* game , RenderingEngine* renderingEngine);
    void start(){ m_running = true;}
    void stop() { m_running = false;}
    void run();
    bool is_running() { return m_running;}
    virtual ~CoreEngine();
private:
    bool m_running;
    RenderingEngine* renderingEngine;
    Display* m_display;
    Game* m_game;
    CoreEngine(const CoreEngine& other) {}
    CoreEngine& operator=(const CoreEngine& other) {}
};

#endif // COREENGINE_H

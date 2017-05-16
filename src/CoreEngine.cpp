#include "CoreEngine.h"
#include "display.h"
#include"GUIManager.h"

CoreEngine::CoreEngine(Display* display, Game* game ,RenderingEngine* renderingEngine , GUIManager* m)
{
    m_running = false;
    this->m_game = game;
    this->renderingEngine = renderingEngine;
    this->m_display = display;
    this->m_guiManager = m;
    //game->getRootObject()->setEngine(this);
    renderingEngine->setCoreEngine(this);
}
void CoreEngine::run()
{
    if(!m_running )
        return;
    if(!m_display->isRunning())
        stop();
    m_display->Clear(0.3f, 0.3f, 0.3f, 1.0f);

    m_display->update();
    renderingEngine->render(m_game->getRootObject());
    m_guiManager->renderGUI();
    m_game->update();


    m_display->SwapBuffers();
}
CoreEngine::~CoreEngine()
{
    //dtor
}

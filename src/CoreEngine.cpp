#include "CoreEngine.h"
#include "display.h"
#include"GUIManager.h"
#include"PostProcess.h"

CoreEngine::CoreEngine(Display* display, Game* game ,RenderingEngine* renderingEngine , GUIManager* m)
{
    m_running = false;
    m_deltaTime = 0.01f;
    this->m_game = game;
    this->renderingEngine = renderingEngine;
    this->m_display = display;
    this->m_guiManager = m;
    this->m_postProcessManager = new PostProcess(display , renderingEngine);

    //game->getRootObject()->setEngine(this);
    renderingEngine->setScene(m_postProcessManager->getBaseTexture());
    renderingEngine->setCoreEngine(this);
}
void CoreEngine::run()
{
    float t1 = SDL_GetTicks();
    if(!m_running )
        return;
    if(!m_display->isRunning())
        stop();
    m_display->Clear(0.3f, 0.3f, 0.3f, 1.0f);

    m_display->update();
    renderingEngine->render(m_game->getRootObject());
    m_postProcessManager->applyPostProcess();
    m_guiManager->renderGUI();
    m_game->update();


    m_display->SwapBuffers();
    float t2 = SDL_GetTicks();
    m_deltaTime = (t2 - t1)/60.0f;
}
CoreEngine::~CoreEngine()
{
    //dtor
}

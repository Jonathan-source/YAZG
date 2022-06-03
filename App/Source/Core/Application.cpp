#include "pch.h"
#include "Application.h"
#include "Core/Config.h"

Application::Application()
    : m_sceneStateMachine(StateMachine())
{
    SetupEngine();
    SetupGameScenes();
}

void Application::Run()
{    
    IState* currentState = nullptr;
    while (!WindowShouldClose() && m_isRunning)
    {
        currentState = m_sceneStateMachine.Current();
        
        // Update Lua?

        currentState->OnInput();

        m_isRunning = currentState->OnUpdate(GetFrameTime());

        currentState->OnRender();

        DrawFPS(10, 10);
    }
}

void Application::SetupEngine()
{
    const int screenWidth = 1280;
    const int screenHeight = 800;
    m_isRunning = true;

    InitWindow(screenWidth, screenHeight, "Yet Another Zombie Game");
    SetExitKey(KEY_NULL);

    InitAudioDevice();

    SetTargetFPS(60);
}

void Application::SetupGameScenes()
{
    m_sceneStateMachine.Add("MainMenu", new MainMenu());
    m_sceneStateMachine.Add("Game", new Game());
    m_sceneStateMachine.Add("Highscore", new Highscore());
    m_sceneStateMachine.Add("Editor", new Editor());

	// Set initial scene
    m_sceneStateMachine.Change("MainMenu");
}
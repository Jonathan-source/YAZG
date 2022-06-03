#pragma once

#include "raylib.h"
#include "Entities/Player.h"
#include "Core/StateMachine.h"
#include "States/MainMenu.h"
#include "States/Game.h"
#include "States/Highscore.h"
#include "Editor/Editor.h"

class Application
{
public:
    Application();
    virtual ~Application() = default;

    void Run();
    
private:
    StateMachine m_sceneStateMachine;
    bool m_isRunning;
    void SetupEngine();

    void SetupGameScenes();
};
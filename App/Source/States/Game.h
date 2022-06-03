#pragma once

#include "Entities/Player.h"
#include "Core/StateMachine.h"
#include "Core/BulletHandler.h"
#include "Core/EnemyManager.h"
#include "Core/PathFinderManager.h"
#include "Entities/Enemy.h"

class Game : public IState
{
public:
	Game() = default;
	virtual ~Game();

	void OnEnter() override;
	void OnInput() override;
	void UpdateCamera();
	bool OnUpdate(float frameDelta) override;
	void RenderGrid();
	void OnRender() override;
	void OnExit() override;
	void InitCamera();

private:
	Camera m_camera;
	Player m_player;
	Enemy m_enemy;
	EnemyManager m_enemyManager;
	BulletHandler m_bulletHandler;
	std::vector<std::vector<Node*>> m_grid;
};

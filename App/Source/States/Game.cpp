#include "pch.h"

#include "States/Game.h"
#include "Core/CollisionHandler.h"


Game::~Game()
{
	for (const auto& nodeVec : m_grid)
	{
		for (auto node : nodeVec)
		{
			delete node;
		}
	}
}

void Game::OnEnter()
{
	InitCamera();
	m_enemyManager.AddSpawnPoint({ 5,0,5 });
	m_enemyManager.AddSpawnPoint({ 15,0,5 });
	m_enemyManager.AddSpawnPoint({ 5,0,15 });
	m_enemyManager.AddSpawnPoint({ 15,0,15 });

	// init grid
	m_grid = PathFinderManager::InitializeGrid(1);

	m_grid[3][3]->reachable = false;
	m_grid[3][4]->reachable = false;
	m_grid[3][5]->reachable = false;
	m_grid[2][3]->reachable = false;
	m_grid[2][4]->reachable = false;
	m_grid[2][5]->reachable = false;

	PathFinderManager::UpdateConnections(m_grid);

	// init enemies
	for (int i = 0; i < 11; i++)
		m_enemyManager.SpawnEnemy(EnemyType::DEFAULT, &m_player, m_grid);

}

void Game::OnInput()
{
	// Get ray and test against objects
	Ray ray = GetMouseRay(GetMousePosition(), m_camera);
	m_player.PlayerInput(ray);
	m_player.Shoot(m_bulletHandler);

	// Toggle menu.
	if (IsKeyPressed(KEY_ESCAPE))
	{
		GetStateMachine()->Change("MainMenu");
	}
}

void Game::UpdateCamera()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_dofile(L, SCRIPT_PATH("GameConfig.lua"));
	lua_getglobal(L, "Camera");

	if (lua_istable(L, -1))
	{
		lua_pushstring(L, "Fov");
		lua_gettable(L, -2);
		m_camera.fovy = lua_tonumber(L, -1);
		lua_pop(L, 1);
	}

	lua_close(L);

	m_camera.position = Vector3Add(m_player.GetPosition(), {0,10,-5});
	m_camera.target = m_player.GetPosition();
}

bool Game::OnUpdate(float frameDelta)
{
	// Update Player.
	m_player.Move(m_player.GetVelocity(), frameDelta, m_player.GetRunSpeed());
	m_player.Update();
	// Update enemies
	m_enemyManager.UpdateEnemies();
	// Update Camera.
	UpdateCamera();
	//Update Bullets
	m_bulletHandler.UpdateBullets();

	CollisionHandler::CheckBulletEnemy(m_enemyManager.GetEnemies(), m_bulletHandler.GetBullets());

	return true;
}

void Game::RenderGrid()
{
	for(int i = 0; i < m_grid.size(); i++)
	{
		for(int j = 0;j<m_grid.size(); j++)
		{
			if(m_grid.at(i).at(j)->reachable)
				DrawCube(m_grid.at(i).at(j)->position, 0.2f, 0.2f, 0.2f, RED);
			else
				DrawCube(m_grid.at(i).at(j)->position, 0.2f, 0.2f, 0.2f, BLUE);
		}
	}
}

void Game::OnRender()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	BeginMode3D(m_camera);
	DrawModel(m_player.GetModel(), m_player.GetPosition(), 1.0f, WHITE);
	m_bulletHandler.RenderBullets();
	m_enemyManager.RenderEnemies();
	RenderGrid();
	DrawCubeWires({ 0,0,0 }, 2.0f, 2.0f, 2.0f, MAROON);
	DrawGrid(10, 1.0f);
	EndMode3D();

	EndDrawing();
}

void Game::OnExit()
{

}

void Game::InitCamera()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_dofile(L, "C:/Dev/YAZG/App/Assets/Scripts/GameConfig.lua");
	lua_getglobal(L, "Camera");

	if(lua_istable(L, -1))
	{
		lua_pushstring(L, "Fov");
		lua_gettable(L, -2);
		m_camera.fovy = lua_tonumber(L, -1);
		lua_pop(L, 1);
	}

	// Define the camera to look into our 3d world
	m_camera.position = { 0.0f, 10.0f, 10.0f };  // Camera position
	m_camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	m_camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	//m_camera.fovy = 45.0f;                                // Camera field-of-view Y
	m_camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	lua_close(L);
}



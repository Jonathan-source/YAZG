#pragma once

#include "Entities/Enemy.h"

enum class EnemyType { DEFAULT, TYPE1, TYPE2 };

class EnemyManager
{
public:
	// Constructor
	EnemyManager();
	// Deconstructor
	~EnemyManager();
	// Getters
	[[nodiscard]] std::vector<Enemy*>& GetEnemies();
	[[nodiscard]] std::vector<Vector3>& GetSpawnPoints();

	// Setters 

	// Functions
	void AddSpawnPoint(Vector3 spawnPoint);
	void SpawnEnemy(EnemyType enemyType, Player* playerTarget, const std::vector<std::vector<Node*>>& grid);
	void UpdateEnemies() ;
	void RenderEnemies() const;

private:
	std::vector<Enemy*> m_enemies;
	std::vector<Vector3> m_spawnPoints;
	int currentSpawnIndex;
};


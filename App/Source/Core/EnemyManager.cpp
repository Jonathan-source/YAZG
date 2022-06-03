#include "pch.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
	:currentSpawnIndex(0)
{

}

EnemyManager::~EnemyManager()
{
	for (auto enemy : m_enemies)
	{
		delete enemy;
	}
}

std::vector<Enemy*>& EnemyManager::GetEnemies()
{
	return m_enemies;
}

std::vector<Vector3>& EnemyManager::GetSpawnPoints()
{
	return m_spawnPoints;
}

void EnemyManager::AddSpawnPoint(Vector3 spawnPoint)
{
	m_spawnPoints.push_back(spawnPoint);
}

void EnemyManager::SpawnEnemy(EnemyType enemyType, Player* playerTarget, const std::vector<std::vector<Node*>>& grid)
{

	switch (enemyType)
	{
	case EnemyType::DEFAULT:
		{
			const auto enemy = new Enemy;
			currentSpawnIndex = ++currentSpawnIndex % m_spawnPoints.size();
			enemy->SetPosition(m_spawnPoints[currentSpawnIndex]);
			enemy->SetPlayerTarget(playerTarget);
			enemy->SetGrid(grid);
			m_enemies.push_back(enemy);
		}
		break;
	case EnemyType::TYPE1: break;
	case EnemyType::TYPE2: break;
	default:
		break;
	}
}

void EnemyManager::UpdateEnemies() 
{
	// Update & Move Enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies.at(i)->Update();
		m_enemies.at(i)->Move(m_enemies.at(i)->GetVelocity(), GetFrameTime(), m_enemies.at(i)->GetRunSpeed());

		if (m_enemies.at(i)->GetHealth() <= 0)
		{
			delete m_enemies.at(i);
			m_enemies.erase(m_enemies.begin() + i);
		}
	}
}

void EnemyManager::RenderEnemies() const
{
	for (const auto enemy : m_enemies)
	{
		DrawModel(enemy->GetModel(), enemy->GetPosition(), 1, WHITE);
	}
}

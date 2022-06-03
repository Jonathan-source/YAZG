#include "pch.h"

#include "Entities/Enemy.h"
#include "Core/PathFinderManager.h"

Enemy::Enemy()
	: Entity()
	, m_health(100)
	, m_attackDmg(1)
	, m_runSpeed(3.f + static_cast<float>((rand() % 5) / 10.f)), m_velocity({ 0.f, 0.f, 0.f })
	, m_direction({ 0.f, 0.f, })
{
	SetModel(LoadModel(MESH_PATH("zombie.obj")));
	this->m_texture = LoadTexture(TEXTURE_PATH("zombie.png"));
	m_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_texture;
	m_boundingBox = GetMeshBoundingBox(m_model.meshes[0]);
}

Enemy::Enemy(Player* playerTarget)
	: Entity()
	, m_health(100)
	, m_attackDmg(1)
	, m_runSpeed(5)
	, m_velocity({ 0.f, 0.f, 0.f })
	, m_direction({ 0.f, 0.f, })
	, m_playerTarget(playerTarget)
{
	SetModel(LoadModel(MESH_PATH("zombie.obj")));
	this->m_texture = LoadTexture(TEXTURE_PATH("zombie.png"));
	m_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_texture;
	m_boundingBox = GetMeshBoundingBox(m_model.meshes[0]);
}


Enemy::~Enemy()
= default;

int Enemy::GetHealth() const
{
	return m_health;
}

int Enemy::GetAttackDamage() const
{
	return m_attackDmg;
}

float Enemy::GetRunSpeed() const
{
	return m_runSpeed;
}

Vector2 Enemy::GetDirection() const
{
	return m_direction;
}

void Enemy::SetHealth(int health)
{
	m_health = health;
}

void Enemy::SetAttackDamage(int attdmg)
{
	m_attackDmg = attdmg;
}

void Enemy::SetRunSpeed(float runSpeed)
{
	m_runSpeed = runSpeed;
}

void Enemy::SetTexture(Texture2D texture)
{
	m_texture = texture;
}

void Enemy::SetVelocity(const Vector3& velocity)
{
	m_velocity = velocity;
}

void Enemy::SetPlayerTarget(Player* playerTarget)
{
	m_playerTarget = playerTarget;
}

void Enemy::SetBoundingBox(BoundingBox boundingBox)
{
	m_boundingBox = boundingBox;
}

void Enemy::SetGrid(const std::vector<std::vector<Node*>>& grid)
{
	m_grid = grid;
}

void Enemy::MoveOnPath()
{
	Node* closestNode = PathFinderManager::GetClosestNode(GetPosition(), m_grid);

	// Generate path with A-star
	path = PathFinderManager::AStar(closestNode, PathFinderManager::GetClosestNode(m_playerTarget->GetPosition(), m_grid));

	// Move on path
	if (!path.empty())
	{
		m_direction = { path.back()->position.z - closestNode->position.z,  path.back()->position.x - closestNode->position.x };
	}
	else
	{
		// Stop on empty path
		m_direction = { 0,0 };
		m_velocity = { 0, 0.0, 0};
		return;
	}

	// Give velocity depending on the direction for the next node
	m_direction = Vector2Normalize(m_direction);
	m_velocity = { m_direction.y, 0.0, m_direction.x };

	// Rotate towards target
	const float angle = atan2f(m_direction.x, m_direction.y);
	m_model.transform = MatrixRotateXYZ({ 0, angle, 0 });
}

void Enemy::Update()
{
	// Generate path and move
	MoveOnPath();
}

void Enemy::TakeDamage(int damage)
{
	m_health -= damage;
}


Vector3 Enemy::GetVelocity() const
{
	return m_velocity;
}

Texture2D Enemy::GetTexture() const
{
	return m_texture;
}

BoundingBox Enemy::GetBoundingBox() const
{
	return m_boundingBox;
}

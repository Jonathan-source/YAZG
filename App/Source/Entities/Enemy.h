#pragma once
#include "Player.h"

struct Node;

class Enemy : public Entity 
{
public:
	Enemy();
	Enemy(Player* playerTarget);
	~Enemy();

	//Getters
	[[nodiscard]] int GetHealth() const;
	[[nodiscard]] int GetAttackDamage() const;
	[[nodiscard]] float GetRunSpeed() const;
	[[nodiscard]] Vector2 GetDirection() const;
	[[nodiscard]] Vector3 GetVelocity() const;
	[[nodiscard]] Texture2D GetTexture() const;
	[[nodiscard]] BoundingBox GetBoundingBox() const;

	//Setters
	void SetHealth(int health);
	void SetAttackDamage(int attdmg);
	void SetRunSpeed(float runSpeed);
	void SetTexture(Texture2D texture);
	void SetVelocity(const Vector3& velocity);
	void SetPlayerTarget(Player* playerTarget);
	void SetBoundingBox(BoundingBox boundingBox);
	void SetGrid(const std::vector<std::vector<Node*>>& grid);


	//Functions
	void Update();
	void TakeDamage(int damage);
	void MoveOnPath();
private:
	int m_health;
	int m_attackDmg;
	float m_runSpeed;
	BoundingBox m_boundingBox;
	Vector3 m_velocity;
	Vector2 m_direction;
	Texture2D m_texture{};
	Player* m_playerTarget;

	std::vector<Node*> path;
	std::vector<std::vector<Node*>> m_grid;
};


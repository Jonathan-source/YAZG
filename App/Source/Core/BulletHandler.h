#pragma once

#include "Entities/Projectile.h"

class BulletHandler
{
public:
	// Constructor
	BulletHandler();
	// Deconstructor
	~BulletHandler();
	// Getters
	std::vector<Projectile*>& GetBullets();
	// Functions
	void SpawnBullet(Bullet bulletType, Vector3 direction, Vector3 spawnPosition, float angle);
	void UpdateBullets();
	void RenderBullets() const;
private:
	// Data
	Model m_bulletModel;
	BoundingBox m_bulletBounds;
	Texture2D m_bulletTexture;
	std::vector<Projectile*> m_bullets;
};


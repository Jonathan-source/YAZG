#pragma once
#include <raylib.h>

#include "Entity.h"
enum class Bullet{DEFAULT, TYPE1, TYPE2 };

class Projectile : public Entity
{
public:
	//Constructors
	Projectile();
	Projectile(Vector3 position, Vector3 velocity, bool isActive, float lifeSpawn);
	//Getters
	[[nodiscard]] bool GetIsActive() const;
	[[nodiscard]] float GetLifeSpawn() const;
	[[nodiscard]] Vector3 GetVelocity() const;
	[[nodiscard]] Bullet GetBulletType() const;
	[[nodiscard]] float GetBulletSpeed() const;
	[[nodiscard]] int GetBulletDamage() const;
	//Setters
	void SetVelocity(Vector3 velocity);
	void SetIsActive(bool condition);
	void SetLifeSpawn(float lifeSpawn);
	void SetBulletType(Bullet bulletType);
	void SetBulletSpeed(float speed);
	void SetBulletDamage(float dmg);
private:
	//Data
	bool m_isActive;
	float m_dmg;
	float m_lifeSpawn;
	float m_bulletSpeed;
	Bullet m_bulletType;
	Vector3 m_velocity;
};


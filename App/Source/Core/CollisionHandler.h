#pragma once
class Projectile;
class Enemy;

class CollisionHandler
{
public:
	// Functions
	static void CheckBulletEnemy(std::vector<Enemy*>& enemies, std::vector<Projectile*>& bullets);
private:

};


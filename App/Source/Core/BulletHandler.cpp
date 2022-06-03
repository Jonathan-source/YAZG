#include "pch.h"
#include "BulletHandler.h"

BulletHandler::BulletHandler()
{
	m_bulletModel = LoadModel(MESH_PATH("bullet.obj"));
	m_bulletBounds = GetMeshBoundingBox(m_bulletModel.meshes[0]);
	//m_bulletTexture = LoadTexture("../resources/textures/Steve.png");
	//m_bulletModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_bulletTexture;
}

BulletHandler::~BulletHandler()
{
	for (const auto bullet : m_bullets)
	{
		delete bullet;
	}
	UnloadModel(m_bulletModel);
}

std::vector<Projectile*>& BulletHandler::GetBullets()
{
	return m_bullets;
}

void BulletHandler::SpawnBullet(Bullet bulletType, Vector3 direction, Vector3 spawnPosition, float angle)
{
	switch (bulletType)
	{
	case Bullet::DEFAULT: 
	{
		auto projectile = new Projectile(Vector3Add(spawnPosition, {0,1,0}), direction, true, 3.f);
		projectile->SetBulletSpeed(20.f);
		m_bulletModel.transform = m_bulletModel.transform = MatrixRotateXYZ({ 0, angle, 0 });
		
		projectile->SetModel(m_bulletModel);
		projectile->SetBoundingBox(m_bulletBounds);
		m_bullets.emplace_back(projectile);
	}
		break;
	//case Bullet::TYPE1:
	//	break;
	//case Bullet::TYPE2:
	//	break;
	default:
		break;
	}
}

void BulletHandler::UpdateBullets()
{
	// Move Bullets
	for (const auto bullet : m_bullets)
	{
		bullet->Move(bullet->GetVelocity(), GetFrameTime(), bullet->GetBulletSpeed());
		bullet->SetLifeSpawn(bullet->GetLifeSpawn() - GetFrameTime());
	}
	// Erase dead bullets
	bool hasDeadBullets = true;
	while(hasDeadBullets && !m_bullets.empty())
	{
		if (m_bullets.back()->GetLifeSpawn() <= 0.01f || !m_bullets.back()->GetIsActive())
		{
			delete m_bullets.back();
			m_bullets.pop_back();
		}
		else
			hasDeadBullets = false;
	}

}

void BulletHandler::RenderBullets() const
{
	for (const auto bullet : m_bullets)
	{
		if(bullet->GetIsActive())
			DrawModel(bullet->GetModel(),bullet->GetPosition(),1, WHITE);
	}
	
}

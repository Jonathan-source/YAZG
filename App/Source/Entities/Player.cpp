#include "pch.h"

#include "Entities/Player.h"
#include "Core/BulletHandler.h"

Player::Player()
	: Entity()
	, m_health(100)
	, m_attackDmg(1)
	, m_runSpeed(5)
	, m_shootTimer(0.0f)
	, m_shootCooldown(0.25f)
	, m_velocity({0.f, 0.f, 0.f})
	, m_direction({0.f, 0.f,})
	, m_bulletType(Bullet::DEFAULT)

{
	SetModel(LoadModel("C:/Dev/YAZG/App/Assets/Meshes/steve.obj"));
	this->m_texture = LoadTexture("C:/Dev/YAZG/App/Assets/Textures/Steve.png");
	m_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_texture;
	m_model.transform = MatrixRotateXYZ({ 0, DEG2RAD * 90, 0 });
}

Player::Player(int health, int attdmg, float runSpeed, Vector3 position)
	: Entity(position)
	, m_health(health)
	, m_attackDmg(attdmg)
	, m_runSpeed(runSpeed)
	, m_shootTimer(0.0f)
	, m_shootCooldown(0.25f)
	, m_velocity({0.f, 0.f, 0.f})
	, m_direction({0.f, 0.f,})
	, m_bulletType(Bullet::DEFAULT)
{
	SetModel(LoadModel(".C:/Dev/YAZG/App/Assets/Meshes/steve.obj"));
	// Tranformation matrix for rotations
	m_model.transform = MatrixRotateXYZ( { 0, DEG2RAD * 90, 0 });
	this->m_texture = LoadTexture("C:/Dev/YAZG/App/Assets/Textures/Steve.png");
	m_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_texture;
}

int Player::GetHealth() const
{
	return this->m_health;
}

int Player::GetAttackDamage() const
{
	return this->m_attackDmg;
}

float Player::GetRunSpeed() const
{
	return this->m_runSpeed;
}

Vector2 Player::GetDirection() const
{
	return Vector2Normalize(m_direction);
}

float Player::GetAngle() const
{
	return m_angle;
}

void Player::SetHealth(int health)
{
	this->m_health = health;
}

void Player::SetAttackDamage(int attdmg)
{
	this->m_attackDmg = attdmg;
}

void Player::SetRunSpeed(float runSpeed)
{
	this->m_runSpeed = runSpeed;
}

void Player::SetTexture(Texture2D texture)
{
	m_texture = texture;
}

void Player::PlayerInput(const Ray &ray)
{
	if (IsKeyDown(KEY_A))
		m_velocity.x = 1.0f;

	if (IsKeyDown(KEY_W))
		m_velocity.z = 1.0f;

	if (IsKeyDown(KEY_D))
		m_velocity.x = -1.0f;

	if (IsKeyDown(KEY_S))
		m_velocity.z = -1.0f;

	if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
		m_velocity.x = 0;

	if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S))
		m_velocity.z = 0;

	RotateWithMouse(ray);
}

void Player::Shoot(BulletHandler& bulletHandler)
{

	if (IsKeyDown(KEY_C) && m_shootTimer < 0.01f)
	{
		// spawn bullet
		bulletHandler.SpawnBullet(m_bulletType, { m_direction.x , 0.f, -m_direction.y }, this->GetPosition(), m_angle);
		// reset timer
		m_shootTimer = m_shootCooldown;
	}
		
}

void Player::TakeDamage(const int damage)
{
	m_health -= damage;
}

void Player::Update()
{
	m_shootTimer -= GetFrameTime();
}

Vector3 Player::GetVelocity() const
{
	return m_velocity;
}

Texture2D Player::GetTexture() const
{
	return m_texture;
}

Bullet Player::GetBulletType() const
{
	return m_bulletType;
}

void Player::SetVelocity(const Vector3& velocity)
{
	this->m_velocity = velocity;
}

void Player::SetBulletType(Bullet bulletType)
{
	m_bulletType = bulletType;

	switch (m_bulletType)
	{
	case Bullet::DEFAULT:
		m_shootCooldown = 0.25f;
		break;
	case Bullet::TYPE1:
		m_shootCooldown = 0.15f;
		break;
	case Bullet::TYPE2:
		m_shootCooldown = 0.10f;
		break;
	}
}

void Player::RotateWithMouse(const Ray& ray)
{
	// Ground quad
	constexpr float SIZE = 1000.f;
	constexpr Vector3 g0 = { -SIZE, 0.0f, -SIZE };
	constexpr Vector3 g1 = { -SIZE, 0.0f, SIZE };
	constexpr Vector3 g2 = { SIZE, 0.0f, SIZE };
	constexpr Vector3 g3 = { SIZE, 0.0f, -SIZE };

	// Check ray collision against ground quad
	const RayCollision groundHitInfo = GetRayCollisionQuad(ray, g0, g1, g2, g3);
	m_direction = { groundHitInfo.point.z - GetPosition().z, groundHitInfo.point.x - GetPosition().x };
	m_direction = Vector2Normalize(m_direction);
	m_angle = atan2f(m_direction.x, m_direction.y);
	m_direction = Vector2Rotate(m_direction, DEG2RAD * -90); // i don't know why -90 degree but it works?
	m_model.transform = MatrixRotateXYZ({ 0, m_angle, 0 });
}

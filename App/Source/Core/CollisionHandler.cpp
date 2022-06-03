#include "pch.h"

#include "Core/CollisionHandler.h"
#include "Entities/Enemy.h"
#include "Entities/Projectile.h"

void CollisionHandler::CheckBulletEnemy(std::vector<Enemy*>& enemies, std::vector<Projectile*>& bullets)
{
	for (const auto bullet : bullets)
	{
		for (const auto enemy : enemies)
		{
            
            // Check collisions Enemy vs bullet
            if (bullet->GetIsActive() && CheckCollisionBoxes(BoundingBox{Vector3{
                    enemy->GetPosition().x + enemy->GetBoundingBox().min.x,
            	    enemy->GetPosition().y + enemy->GetBoundingBox().min.y,
            	    enemy->GetPosition().z + enemy->GetBoundingBox().min.z,
            },Vector3{
                    enemy->GetPosition().x + enemy->GetBoundingBox().max.x,
                    enemy->GetPosition().y + enemy->GetBoundingBox().max.y,
                    enemy->GetPosition().z + enemy->GetBoundingBox().max.z,
                }
            },BoundingBox{
                Vector3{
					bullet->GetPosition().x + bullet->GetBoundingBox().min.x,
                    bullet->GetPosition().y + bullet->GetBoundingBox().min.y,
                    bullet->GetPosition().z + bullet->GetBoundingBox().min.z,
            },
                    Vector3 {
					bullet->GetPosition().x + bullet->GetBoundingBox().max.x,
                    bullet->GetPosition().y + bullet->GetBoundingBox().max.y,
                    bullet->GetPosition().z + bullet->GetBoundingBox().max.z,
                }
            }))
            {
                // Deactivate bullet
                bullet->SetIsActive(false);
                // Damage enemy
                enemy->TakeDamage(bullet->GetBulletDamage());
            }
		}
	}

}

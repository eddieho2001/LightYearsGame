#include "Enemy/TwinBlade.h"
#include "weapon/BulletShooter.h"

ly::TwinBlade::TwinBlade(World* ptrOwner, const std::string& texturePath, const sf::Vector2f& velocity)
	:EnemySpaceship{ ptrOwner, texturePath },
	mLeftShooter{ new BulletShooter{this, 1.f, {-30.f, 0.f}} },
	mRightShooter{ new BulletShooter{this, 1.f, {30.f, 0.f}} }
{
	SetVelocity(velocity);
}

void ly::TwinBlade::Tick(float deltaTime)
{
	EnemySpaceship::Tick(deltaTime);
	Shoot();
}

void ly::TwinBlade::Shoot()
{
	mLeftShooter->Shoot();
	mRightShooter->Shoot();
}

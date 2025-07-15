#include "Enemy/Vanguard.h"
#include "weapon/BulletShooter.h"

ly::Vanguard::Vanguard(World* ptrOwner, const std::string& texturePath, const sf::Vector2f& velocity)
	:EnemySpaceship{ ptrOwner, texturePath },
	mShooter{ new BulletShooter{this, 1.f, {0.f, 0.f}} }
{
	SetVelocity(velocity);
	//SetRotation(-180.f);
}

void ly::Vanguard::Tick(float deltaTime)
{
	EnemySpaceship::Tick(deltaTime);
	Shoot();
}

void ly::Vanguard::Shoot()
{
	mShooter->Shoot();
}

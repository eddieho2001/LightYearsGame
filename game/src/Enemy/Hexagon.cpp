#include "Enemy/Hexagon.h"
#include "weapon/BulletShooter.h"

ly::Hexagon::Hexagon(World* ptrOwner, const std::string& texturePath, const sf::Vector2f& velocity)
	:EnemySpaceship{ ptrOwner, texturePath },
	mShooter01{ new BulletShooter{this, 1.f, {20.f, 50.f}, 30.f }},
	mShooter02{ new BulletShooter{this, 1.f, {20.f, -50.f}, -30.f } },
	mShooter03{ new BulletShooter{this, 1.f, {50.f, 0.f}}},
	mShooter04{ new BulletShooter{this, 1.f, {-50.f, 0.f}, -180.f } },
	mShooter05{ new BulletShooter{this, 1.f, {-20.f, 50.f}, -120.f } },
	mShooter06{ new BulletShooter{this, 1.f, {-20.f, -50.f}, 120.f } }
{
	SetVelocity(velocity);
}

void ly::Hexagon::Tick(float deltaTime)
{
	EnemySpaceship::Tick(deltaTime);
	Shoot();
}

void ly::Hexagon::Shoot()
{
	mShooter01->Shoot();
	mShooter02->Shoot();
	mShooter03->Shoot();
	mShooter04->Shoot();
	mShooter05->Shoot();
	mShooter06->Shoot();
}

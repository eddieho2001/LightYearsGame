#pragma once

#include "Enemy/EnemySpaceship.h"

namespace ly {
	class BulletShooter;
	class Hexagon : public EnemySpaceship {
	public:
		Hexagon(World* ptrOwner, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyGreen4.png", const sf::Vector2f& velocity = { 0.f,150.f });
		virtual void Tick(float deltaTime) override;
	private:
		virtual void Shoot() override;
	private:
		unique<BulletShooter> mShooter01;
		unique<BulletShooter> mShooter02;
		unique<BulletShooter> mShooter03;
		unique<BulletShooter> mShooter04;
		unique<BulletShooter> mShooter05;
		unique<BulletShooter> mShooter06;
	};
}
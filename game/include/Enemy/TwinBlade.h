#pragma once

#include "Enemy/EnemySpaceship.h"

namespace ly {
	class BulletShooter;
	class TwinBlade : public EnemySpaceship {
	public:
		TwinBlade(World* ptrOwner, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png", const sf::Vector2f& velocity = { 0.f,120.f });
		virtual void Tick(float deltaTime) override;
	private:
		virtual void Shoot() override;
	private:
		/*
		 * Note that there are two shooter and at current setting for BulletShooter there are noway to configure offset position
		 * for the second shooter shoot bullet.
		 * Hence, we need to change/enhanced BulletShooter code.
		 */
		unique<BulletShooter> mLeftShooter;
		unique<BulletShooter> mRightShooter;

	};
}
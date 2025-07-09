#pragma once

#include "Enemy/EnemySpaceship.h"
#include<SFML/Graphics.hpp>


namespace ly {
	class BulletShooter;
	class Vanguard : public EnemySpaceship {
	public:
		Vanguard(World* ptrOwner, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlue1.png", const sf::Vector2f& velocity = {0.f,150.f});
		virtual void Tick(float deltaTime) override;
	private:
		virtual void Shoot() override;
	private:
		unique<BulletShooter> mShooter;
	};
}
#pragma once

#include "spaceship/Spaceship.h"

namespace ly {
	class EnemySpaceship : public Spaceship {
	public:
		EnemySpaceship(World* ptrOwner, const std::string& texturePath = "", float collisionDamage = 200.f);
		virtual void Tick(float deltaTime) override;

	private:
		virtual void OnActorBeginOverlap(Actor* other) override;
		virtual void OnActorEndOverlap(Actor* other) override;
	private:
		float mCollisionDamage;

	};
}
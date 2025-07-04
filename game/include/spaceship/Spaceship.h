#pragma once
#include <framework/Actor.h>
#include "gameplay/HealthComponent.h"

namespace ly {
	class Spaceship : public Actor {
	public:
		Spaceship(World* ptrOwner, const std::string& texturePath="");
		virtual void Tick(float deltaTime) override;
		void SetVelocity(sf::Vector2f& newVelocity);
		sf::Vector2f GetVelocity() const { return mVelocity; }
		virtual void Shoot();

		//After add physics system, we can implement the BeginPlay function
		virtual void BeginPlay() override;

	private:
		sf::Vector2f mVelocity;
		HealthComponent mHealthComp;
	};


}
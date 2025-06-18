#pragma once
#include <framework/Actor.h>

namespace ly {
	class Spaceship : public Actor {
	public:
		Spaceship(World *ptrOwner, std::string& p_strTexturePath);
		virtual void Tick(float deltaTime) override;
		void SetVelocity(sf::Vector2f& newVelocity);
		sf::Vector2f GetVelocity() const { return mVelocity; }
	private:
		sf::Vector2f mVelocity;
	};


}
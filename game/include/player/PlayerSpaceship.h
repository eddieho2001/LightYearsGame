#pragma once
#include "spaceship/Spaceship.h"

namespace ly {
	class PlayerSpaceship : public Spaceship {
	public:
		PlayerSpaceship(World* ptrOwner, const std::string& texturePath="SpaceShooterRedux/PNG/playerShip1_blue.png");
		virtual void Tick(float deltaTime) override;
	private:
		void HandlingInput();
		void ConsumeInput(float deltaTime);
		void SetSpeed(float p_fNewSpeed) { mfSpeed = p_fNewSpeed; }
		float GetSpeed() const { return mfSpeed; }
		void NormalizeInput();
		void ClampInputOnEdge();
	private:
		sf::Vector2f mMoveInput;
		float mfSpeed;
	};
}
#pragma once
#include "spaceship/Spaceship.h"

namespace ly {
	class PlayerSpaceship : public Spaceship {
	public:
		PlayerSpaceship(World* ptrOwner, const std::string& texturePath="SpaceShooterRedux/PNG/playerShip1_blue.png");
	};
}
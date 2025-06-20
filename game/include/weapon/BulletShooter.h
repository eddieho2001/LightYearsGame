#pragma once
#include "weapon/Shooter.h"
#include <SFML/System.hpp>

namespace ly {
	class BulletShooter : public Shooter {
	public:
		BulletShooter(Actor* ptrOwner, float pfTimeForCoolDown = 0.3);
		virtual bool IsOnCooldown() const override;
	private:
		virtual void ShootImpl() override;
		sf::Clock mCoolDownClock;
		float mfTimeForCoolDown;
	};
}
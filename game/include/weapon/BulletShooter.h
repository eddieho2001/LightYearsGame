#pragma once
#include "weapon/Shooter.h"
#include <SFML/System.hpp>

namespace ly {
	class BulletShooter : public Shooter {
	public:
		BulletShooter(Actor* ptrOwner, float pfTimeForCoolDown = 0.3, const sf::Vector2f& localPositionOffset = {0.f,0.f}, float localRotationOffset=0.f);
		virtual bool IsOnCooldown() const override;
	private:
		virtual void ShootImpl() override;
	private:
		sf::Clock mCoolDownClock;
		float mfTimeForCoolDown;
		sf::Vector2f mLocalPositionOffset;
		float mLocalRotationOffset;
	};
}
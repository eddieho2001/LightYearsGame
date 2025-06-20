#include "weapon/BulletShooter.h"
#include <framework/Core.h>

ly::BulletShooter::BulletShooter(Actor* ptrOwner, float pfTimeForCoolDown)
	:Shooter{ ptrOwner },
	mfTimeForCoolDown{ pfTimeForCoolDown },
	mCoolDownClock{}
{
}

bool ly::BulletShooter::IsOnCooldown() const
{
	if (mCoolDownClock.getElapsedTime().asSeconds() > mfTimeForCoolDown) {
		return false;
	}
	
	return true;
	
}

void ly::BulletShooter::ShootImpl()
{
	mCoolDownClock.restart();
	_LOG("[BulletShooter] Shooting");
}

#include "weapon/Shooter.h"
#include <framework/Actor.h>

void ly::Shooter::Shoot()
{
	if (CanShoot() && !IsOnCooldown()) {
		ShootImpl();
	}
}

ly::Shooter::Shooter(Actor* ptrOwner)
	: mOwner{ ptrOwner }
{
	mTeamId = ptrOwner->GetTeamId();
}

#include "weapon/BulletShooter.h"
#include "weapon/Bullet.h"
#include <framework/Core.h>
#include "framework/World.h"


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
	weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActors<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
	
	newBullet.lock()->SetLocation(GetOwner()->GetLocation());
	newBullet.lock()->SetRotation(GetOwner()->GetRotataion());
	
	_LOG("[BulletShooter] Shooting");

}

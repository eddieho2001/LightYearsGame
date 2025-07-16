#include "weapon/BulletShooter.h"
#include "weapon/Bullet.h"
#include <framework/Core.h>
#include "framework/World.h"


ly::BulletShooter::BulletShooter(Actor* ptrOwner, float pfTimeForCoolDown, const sf::Vector2f& localPositionOffset, float localRotationOffset)
	:Shooter{ ptrOwner },
	mfTimeForCoolDown{ pfTimeForCoolDown },
	mCoolDownClock{},
	mLocalPositionOffset{ localPositionOffset },
	mLocalRotationOffset{ localRotationOffset }
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

	sf::Vector2f ownerForwardDir = GetOwner()->GetForwardDirection();

	
	//sf::Vector2f ownerRightDir = GetOwner()->GetLeftDirection();
	//sf::Vector2f ownerRightDir = GetOwner()->GetRightDirection();

	mCoolDownClock.restart();
	weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActors<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
	if (GetTeamId() == 1) {
		newBullet.lock()->SetLocation(GetOwner()->GetLocation() + ownerForwardDir * mLocalPositionOffset.x + GetOwner()->GetLeftDirection() * mLocalPositionOffset.y);
	}
	else {
		newBullet.lock()->SetLocation(GetOwner()->GetLocation() + ownerForwardDir * mLocalPositionOffset.x + GetOwner()->GetRightDirection() * mLocalPositionOffset.y);
	}
	

	newBullet.lock()->SetRotation(GetOwner()->GetRotataion() + mLocalRotationOffset);
	//newBullet.lock()->SetLocation(GetOwner()->GetLocation());
	//newBullet.lock()->SetRotation(GetOwner()->GetRotataion());
	
	_LOG("[BulletShooter] Shooting");

}

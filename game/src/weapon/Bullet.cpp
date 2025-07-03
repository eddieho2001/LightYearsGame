#include "weapon/Bullet.h"

ly::Bullet::Bullet(World* ptrWorld, Actor* ptrOwner, const std::string& texturePath, float fSpeed, float fDamage)
	:Actor{ ptrWorld , texturePath },
	 mPtrOwner{ ptrOwner },
	 mSpeed{ fSpeed },
	mDamage{ fDamage }
{
}

void ly::Bullet::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);
	Move(deltaTime);

}

void ly::Bullet::Move(float deltaTime)
{
	SetRotation(0.f);
	AddLocationOffset(GetLeftDirection() * mSpeed * deltaTime);

}

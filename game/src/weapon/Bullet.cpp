#include "weapon/Bullet.h"

ly::Bullet::Bullet(World* ptrWorld, Actor* ptrOwner, const std::string& texturePath, float fSpeed, float fDamage)
	:Actor{ ptrWorld , texturePath },
	 mPtrOwner{ ptrOwner },
	 mSpeed{ fSpeed },
	mDamage{ fDamage }
{
	SetTeamId(mPtrOwner->GetTeamId());
}

void ly::Bullet::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);
	Move(deltaTime);
	/*
		Check it for out of bound, destory it(immediately destory will frequently access memory,
		In Application class, TickInternal will call AssetManager cycle clean up, we can add code to handle this situation
	*/
	if (IsOutOfWindowBound()) {
		Destory();
	}

}

void ly::Bullet::BeginPlay()
{
	Actor::BeginPlay();
	SetEnablePhysics(true);
}

void ly::Bullet::OnActorBeginOverlap(Actor* other)
{
	if (IsOtherHostile(other)) {
		other->ApplyDamage(GetDamage());
		Destory();
	}
}

void ly::Bullet::OnActorEndOverlap(Actor* other)
{
	
}

void ly::Bullet::Move(float deltaTime)
{
	SetRotation(0.f);
	if (GetTeamId() == 1) {
		AddLocationOffset(GetLeftDirection() * mSpeed * deltaTime);
	}
	else {
		AddLocationOffset(GetRightDirection() * mSpeed * deltaTime);
	}
}

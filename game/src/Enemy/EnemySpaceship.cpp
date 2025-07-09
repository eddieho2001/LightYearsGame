#include "Enemy/EnemySpaceship.h"

ly::EnemySpaceship::EnemySpaceship(World* ptrOwner, const std::string& texturePath, float collisionDamage)
	:Spaceship{ ptrOwner , texturePath },
	 mCollisionDamage{ collisionDamage }
{
	SetTeamId(2);
}

void ly::EnemySpaceship::Tick(float deltaTime)
{
	Spaceship::Tick(deltaTime);
	if (IsOutOfWindowBound(GetGlobalBounds().width)) {
		Destory();
	}

}

void ly::EnemySpaceship::OnActorBeginOverlap(Actor* other)
{
	Spaceship::OnActorBeginOverlap(other);
	if (IsOtherHostile(other)) {
		other->ApplyDamage(mCollisionDamage);
	}

}

void ly::EnemySpaceship::OnActorEndOverlap(Actor* other)
{
}

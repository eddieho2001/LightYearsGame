#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/sinks/ConsoleSink.h>

#include "spaceship/Spaceship.h"
#include "framework/World.h"

ly::Spaceship::Spaceship(World* ptrOwner, const std::string& texturePath)
	:Actor{ ptrOwner , texturePath },
	mVelocity{}, 
	mHealthComp{100.f, 100.f}
{
	mlogger = quill::Frontend::create_or_get_logger("Spaceship", quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1"));
	mlogger->set_immediate_flush(true);
}

void ly::Spaceship::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);
	AddLocationOffset(GetVelocity() * deltaTime);
}

void ly::Spaceship::SetVelocity(sf::Vector2f& newVelocity)
{
	mVelocity = newVelocity;
}

void ly::Spaceship::Shoot()
{

}

void ly::Spaceship::BeginPlay()
{
	Actor::BeginPlay();
	SetEnablePhysics(true);
	mHealthComp.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
	mHealthComp.onTakenDamage.BindAction(GetWeakRef(), &Spaceship::OnTakenDamage);
	mHealthComp.onHealthEmpty.BindAction(GetWeakRef(), &Spaceship::OnBlow);
	//mHealthComp.onHealthChanged.Broadcast(11.f, 89.f, 100.f);
}

void ly::Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
{
	LOG_INFO(mlogger, "Health changed by {} and is now: {}/{}", amt, health, maxHealth);
}

void ly::Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
{
}

void ly::Spaceship::OnBlow()
{
	Destory();
}

void ly::Spaceship::ApplyDamage(float amt)
{
	mHealthComp.ChangeHealth(-amt);
}



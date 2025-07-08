#include "VFX/Particle.h"
#include "framework/MathUtility.h"

ly::Particle::Particle(World* ptrOwner, const std::string& texturePath):
	Actor{ ptrOwner , texturePath },
	mVelocity{},
	mTimer{},
	mLifeTime{1.f}
{
}

void ly::Particle::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);
	Move(deltaTime);
	Fade(deltaTime);
	if (mTimer.getElapsedTime().asSeconds() >= mLifeTime) {
		Destory();
	}
}

void ly::Particle::RandomVelocity(float minSpeed, float maxSpeed)
{
	mVelocity = GetRandomUnitVector() * RandomRange(minSpeed, maxSpeed);
}

void ly::Particle::RandomSize(float min, float max)
{
	float randScale = RandomRange(min, max);
	GetSprite().setScale(randScale, randScale);
}

void ly::Particle::RandomLiftTime(float min, float max)
{
	mLifeTime = RandomRange(min, max);
}

void ly::Particle::Move(float deltaTime)
{
	AddLocationOffset(mVelocity * deltaTime);
}

void ly::Particle::Fade(float deltaTime)
{
	//because the elapsedTime will become samller and smaller!
	float elapsedTime = mTimer.getElapsedTime().asSeconds();
	GetSprite().setColor( LerpColor( GetSprite().getColor(), sf::Color(255, 255, 255, 0) , elapsedTime/mLifeTime));//it will become more and more transparency 
	GetSprite().setScale(LerpVector(GetSprite().getScale(), sf::Vector2f{ 0.f,0.f }, elapsedTime / mLifeTime));// it will become smaller and smaller
}

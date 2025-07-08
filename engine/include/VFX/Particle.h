#pragma once
#include "framework/Actor.h"

namespace ly {
	/* 
	 * This class responsible for implement VFX effect on spaceship blow up
	 * show it have the following properties:
	 * - lifetime & clock to counting(Randomize)
	 * - it will move so that it have velocity (override parent class BeginPlay() & Tick)(Randomize)
	 * - sprite represent the external look
	 */
	class Particle :public Actor {
	public:
		Particle(World* ptrOwner, const std::string& texturePath = "");
		
		virtual void Tick(float deltaTime) override;
		//For randomize its lifetime, velocity & move we will implement the follow function
		void RandomVelocity(float minSpeed, float maxSpeed);
		void RandomSize(float min, float max);
		void RandomLiftTime(float min, float max);
	private:
		void Move(float deltaTime);
		void Fade(float deltaTime);
	private:
		sf::Vector2f mVelocity;
		sf::Clock mTimer;
		float mLifeTime;
		

	};
}
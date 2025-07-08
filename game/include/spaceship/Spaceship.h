#pragma once
#include <framework/Actor.h>
#include<quill/Logger.h>
#include "gameplay/HealthComponent.h"
#include <SFML/Graphics.hpp>

namespace ly {
	class Spaceship : public Actor {
	public:
		Spaceship(World* ptrOwner, const std::string& texturePath="");
		virtual void Tick(float deltaTime) override;
		void SetVelocity(sf::Vector2f& newVelocity);
		sf::Vector2f GetVelocity() const { return mVelocity; }
		virtual void Shoot();

		//After add physics system, we can implement the BeginPlay function
		virtual void BeginPlay() override;
		virtual void ApplyDamage(float amt) override;
	private:
		virtual void OnHealthChanged(float amt, float health, float maxHealth);
		virtual void OnTakenDamage(float amt, float health, float maxHealth);
		virtual void OnBlow();
		//Mean flash a short period of time  
		void Blink();
		void UpdateBlink(float deltaTime);
	private:
		quill::Logger* mlogger;
		sf::Vector2f mVelocity;
		HealthComponent mHealthComp;

		//For hit blink
		float mBlinkTime;
		float mBlinkDuration;
		sf::Color mBlinkColorOffset;
	};


}
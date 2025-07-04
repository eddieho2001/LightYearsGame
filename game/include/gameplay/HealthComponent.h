#pragma once

#include<quill/Logger.h>

namespace ly {
	class HealthComponent {
	private:
		float mHealth;
		float mMaxHealth;
		quill::Logger* mlogger;
	public:
		HealthComponent(float health, float maxHealth);
		void ChangeHealth(float amount);
		float GetHealth() const{ return mHealth; }
		float GetMaxHealth() const { return mMaxHealth; }
	private:
		void TakeDamage(float amt);
		void HealthEmpty();
		void HealthRegen(float amount);
	};
}

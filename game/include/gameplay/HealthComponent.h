#pragma once

#include<quill/Logger.h>
#include<framework/Delegate.h>

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
		Delegate<float, float, float> onHealthChanged;
		Delegate<float, float, float> onTakenDamage;
		Delegate<> onHealthEmpty;
	private:
		void TakeDamage(float amt);
		void HealthEmpty();
		//void HealthRegen(float amount);
	};
}

#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/sinks/ConsoleSink.h>

#include "gameplay/HealthComponent.h"
#include <framework/MathUtility.h>

ly::HealthComponent::HealthComponent(float health, float maxHealth)
	: mHealth{ health },
	  mMaxHealth{ maxHealth }
{
	mlogger = quill::Frontend::create_or_get_logger("HealthComponent", quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1"));
	mlogger->set_immediate_flush(true);
}

void ly::HealthComponent::ChangeHealth(float amount)
{

	if (amount == epsilon) return;
	if (mHealth == epsilon) return;

	mHealth += amount;
	if (mHealth < epsilon) {
		mHealth = 0;
	}

	if (mHealth > mMaxHealth) {
		mHealth = mMaxHealth;
	}

	if (amount < epsilon) {
		TakeDamage(-amount);
		if (mHealth <= epsilon) {
			HealthEmpty();
		}
	}
	else {
		HealthRegen(amount);
	}
}

void ly::HealthComponent::TakeDamage(float amt)
{
	LOG_INFO(mlogger, "Took Damage: {}, current health is {}/{}", amt, mHealth, mMaxHealth);
}

void ly::HealthComponent::HealthEmpty()
{
	LOG_INFO(mlogger, "Dead: current health is {}/{}", mHealth, mMaxHealth);
}

void ly::HealthComponent::HealthRegen(float amount)
{
	LOG_INFO(mlogger, "Health Regen: {}, current health is {}/{}", amount, mHealth, mMaxHealth);
}

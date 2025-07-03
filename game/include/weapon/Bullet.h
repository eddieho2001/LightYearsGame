#pragma once
#include "framework/Actor.h"

namespace ly {
	class World;
	class Bullet :public Actor {
	public:
		//ptrOwner: Actor stand for who shoot the bullet 
		Bullet(World* ptrWorld, Actor* ptrOwner, const std::string& texturePath, float fSpeed = 300.f, float fDamage = 10.f);
		void SetSpeed(float speed) { mSpeed = speed; }
		float GetSpeed() const { return mSpeed; }
		void SetDamage(float damage) { mDamage = damage; }
		float GetDamage() const { return mDamage; }
		virtual void Tick(float deltaTime) override;
	private:
		void Move(float deltaTime);
	private:
		Actor* mPtrOwner;
		float mSpeed;
		float mDamage;
	};
}
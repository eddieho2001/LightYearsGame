#pragma once
#include "framework/Actor.h"

/* 
 * One of the problem is each fired bullet not yet destory, so that memory is not clean up! 
 * When to clean it up? when the bullet out of the game window bound, it should be destory!
 * 1. check the bullet out of bound(function in Actor: IsOutOfWindowBound())
 * 2. However for game, we want not frequently access memory, and the job is Asset Manager responsibility! 
 */
namespace ly {
	class World;
	class Bullet :public Actor {
	public:
		//ptrOwner: Actor stand for who shoot the bullet 
		Bullet(World* ptrWorld, Actor* ptrOwner, const std::string& texturePath, float fSpeed = 600.f, float fDamage = 10.f);
		void SetSpeed(float speed) { mSpeed = speed; }
		float GetSpeed() const { return mSpeed; }
		void SetDamage(float damage) { mDamage = damage; }
		float GetDamage() const { return mDamage; }
		virtual void Tick(float deltaTime) override;
		//After add physics system, we can implement the BeginPlay function
		virtual void BeginPlay() override;
	private:
		void Move(float deltaTime);
	private:
		Actor* mPtrOwner;
		float mSpeed;
		float mDamage;
	};
}
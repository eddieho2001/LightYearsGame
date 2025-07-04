#pragma once
#include "framework/Core.h"
#include <box2d/b2_world.h>

namespace ly {
	class Actor;
	class PhysicsSystem {
	public:
		static PhysicsSystem& GetInstance();
		void Step(float deltaTime);
		b2Body* AddListener(Actor* ptrListener);
		float GetPhysicsScale() const { return mPhysicsScale; };
		void RemoveListener(b2Body* body);
	protected:
		PhysicsSystem();
	private:
		static unique<PhysicsSystem> mPhysicsSystem;
		b2World mPhysicsWorld;
		float mPhysicsScale;
		int mVelocityIteration;
		int mPositionIteration;
	};
}
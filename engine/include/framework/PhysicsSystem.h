#pragma once
#include<quill/Logger.h>
#include "framework/Core.h"
#include <box2d/b2_world.h>


namespace ly {
	class Actor;

	//By view b2ContactListener it is all vrtual method that Box2D only provided API interface 
	class PhysicsContractListener : public b2ContactListener {
	public:
		PhysicsContractListener();
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
	private:
		quill::Logger* mlogger;
	};

	class PhysicsSystem {
	public:
		static PhysicsSystem& GetInstance();
		void Step(float deltaTime);
		b2Body* AddListener(Actor* ptrListener);
		float GetPhysicsScale() const { return mPhysicsScale; };
		void RemoveListener(b2Body* body);
		static void CleanUp();
	protected:
		PhysicsSystem();
	private:
		void ProcessPendingRemoveListeners();
	private:
		static unique<PhysicsSystem> mPhysicsSystem;
		b2World mPhysicsWorld;
		float mPhysicsScale;
		int mVelocityIteration;
		int mPositionIteration;
		PhysicsContractListener mContractListener;
		//Use set to hold a Listener to be remove from, why bcause the safety issue
		Set<b2Body*> mPendingRemoveListeners;
	};
}
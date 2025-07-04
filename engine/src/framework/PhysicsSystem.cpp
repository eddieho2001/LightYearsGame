#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/sinks/ConsoleSink.h>

#include "framework/PhysicsSystem.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"

#include <box2d/b2_contact.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>



namespace ly {

	unique<PhysicsSystem> ly::PhysicsSystem::mPhysicsSystem{ nullptr };

	PhysicsSystem& PhysicsSystem::GetInstance()
	{
		if (!mPhysicsSystem) {
			mPhysicsSystem = std::move(unique<PhysicsSystem>(new PhysicsSystem()));
		}
		return *mPhysicsSystem;
	}

	void PhysicsSystem::Step(float deltaTime)
	{
		ProcessPendingRemoveListeners();
		mPhysicsWorld.Step(deltaTime, mVelocityIteration, mPositionIteration);
	}

	b2Body* PhysicsSystem::AddListener(Actor* ptrListener)
	{
		if (ptrListener->IsPendingDestory()) return nullptr;
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(ptrListener);
		bodyDef.position.Set(GetPhysicsScale() * ptrListener->GetLocation().x, GetPhysicsScale() * ptrListener->GetLocation().y);//must be scale it 
		bodyDef.angle = Degree2Radian(ptrListener->GetRotataion());//it need to multiple  scale?
		b2Body* body = mPhysicsWorld.CreateBody(&bodyDef);

		b2PolygonShape shape;
		auto bound = ptrListener->GetGlobalBounds();
		shape.SetAsBox(GetPhysicsScale() * bound.width/2.f , GetPhysicsScale() * bound.height/2.f);
		
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.f;
		fixtureDef.friction = 0.3f;
		fixtureDef.isSensor = true;
		body->CreateFixture(&fixtureDef);
		return body;
	}

	void PhysicsSystem::RemoveListener(b2Body* body)
	{
		mPendingRemoveListeners.insert(body);
	}

	void PhysicsSystem::CleanUp()
	{
		mPhysicsSystem = std::move(unique<PhysicsSystem>(new PhysicsSystem()));
	}

	PhysicsSystem::PhysicsSystem() :
		mPhysicsWorld{ b2Vec2{0.f, 0.f} },
		mPhysicsScale{ 0.01f },
		mVelocityIteration{ 8 },
		mPositionIteration{ 3 },
		mContractListener{},
		mPendingRemoveListeners{}
	{
		//How to acknowledge each listener? By set contract listener
		mPhysicsWorld.SetContactListener(&mContractListener);
		mPhysicsWorld.SetAllowSleeping(false);

	}

	void PhysicsSystem::ProcessPendingRemoveListeners()
	{
		for (auto listener : mPendingRemoveListeners) {
			mPhysicsWorld.DestroyBody(listener);
		}
		mPendingRemoveListeners.clear();
	}

	PhysicsContractListener::PhysicsContractListener()
	{
		mlogger = quill::Frontend::create_or_get_logger("PhysicsContractListener", quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1"));
		mlogger->set_immediate_flush(true);
	}

	void PhysicsContractListener::BeginContact(b2Contact* contact)
	{
		//LOG_INFO(mlogger, "Contract Begin");
		Actor* ptrActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		Actor* ptrActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
		if (ptrActorA && !ptrActorA->IsPendingDestory()) {
			ptrActorA->OnActorBeginOverlap(ptrActorB);
		}

		if (ptrActorB && !ptrActorB->IsPendingDestory()) {
			ptrActorB->OnActorBeginOverlap(ptrActorA);
		}
	}
	void PhysicsContractListener::EndContact(b2Contact* contact)
	{
		//Ensure they exist
		Actor* ptrActorA = nullptr;
		Actor* ptrActorB = nullptr;
		if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody()) {
			ptrActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
			
		}

		if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody()) {
			ptrActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
		}

		if (ptrActorA && !ptrActorA->IsPendingDestory()) {
			ptrActorA->OnActorEndOverlap(ptrActorB);
		}

		if (ptrActorB && !ptrActorB->IsPendingDestory()) {
			ptrActorB->OnActorEndOverlap(ptrActorA);
		}
	}
}

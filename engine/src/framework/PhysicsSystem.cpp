#include "framework/PhysicsSystem.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"

#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

namespace ly {

	unique<PhysicsSystem> ly::PhysicsSystem::mPhysicsSystem{ nullptr };

	PhysicsSystem& PhysicsSystem::GetInstance()
	{
		if (!mPhysicsSystem) {
			mPhysicsSystem = unique<PhysicsSystem>(new PhysicsSystem());
		}
		return *mPhysicsSystem;
	}

	void PhysicsSystem::Step(float deltaTime)
	{
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
		//to be impl
	}

	PhysicsSystem::PhysicsSystem():
		mPhysicsWorld{ b2Vec2{0.f, 0.f}},
		mPhysicsScale{0.01f},
		mVelocityIteration{8},
		mPositionIteration{3}
	{
	}
}

#include "framework/World.h"
#include "framework/Actor.h"
#include<SFML/Graphics.hpp>
#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/sinks/ConsoleSink.h>

ly::World::World(Application* ptrOwner)
	:mPtrOwner{ ptrOwner }, 
	 mBeginPlay{false},
	mActors{},
	mPendingActors{}

{
	mlogger = quill::Frontend::create_or_get_logger("World", quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1"));
	mlogger->set_immediate_flush(true);
}

ly::World::~World()
{
	LOG_INFO(mlogger, "World Destructed!");
}

void ly::World::Render(sf::RenderWindow& win)
{
	for (auto& actor : mActors) {
		actor->Render(win);
	}
}

void ly::World::BeginPlayInternal()
{
	if (!mBeginPlay) {
		mBeginPlay = true;
		BeginPlay();
	}
}

void ly::World::TickInternal(float deltaTime)
{
	for (shared<Actor> actor : mPendingActors) {
		mActors.push_back(actor);
		actor->BeginPlayInternal();
	}

	mPendingActors.clear();
	/*
	for (shared<Actor> actor : mActors) {
		actor->Tick(deltaTime);
	}*/
	
	for (auto iter = mActors.begin(); iter != mActors.end();) {
		//check if the actor can be destroy, destroy it
		if (iter->get()->IsPendingDestory()) {
			//After vector erase the target, it will return the next iterator
			iter = mActors.erase(iter);
			//The Actor have been remove from the list, but not yet be destructed!
		}
		else {
			iter->get()->TickInternal(deltaTime);
			++iter;//it also need to increase the iterator
		}
	}

	Tick(deltaTime);
}

void ly::World::Tick(float deltaTime)
{
	//LOG_INFO(mlogger, "Ticking at {}", 1.f/ deltaTime);
}

void ly::World::BeginPlay()
{
	LOG_INFO(mlogger, "World begin play!");
}





#include<SFML/Graphics.hpp>
#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/sinks/ConsoleSink.h>

#include "framework/World.h"
#include "framework/Actor.h"
#include "gameplay/GameStage.h"

ly::World::World(Application* ptrOwner)
	:mPtrOwner{ ptrOwner }, 
	 mBeginPlay{false},
	 mActors{},
	 mPendingActors{},
	 mGameStages{},
	mCurrentStageIter{ mGameStages .end()}
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
		InitGameStages();
		StartStages();
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
		iter->get()->TickInternal(deltaTime);
		++iter;

		//Because the Clean up is done in separate function, so that there are no need to it again here!
		//check if the actor can be destroy, destroy it
		/*
		if (iter->get()->IsPendingDestory()) {
			//After vector erase the target, it will return the next iterator
			iter = mActors.erase(iter);
			//The Actor have been remove from the list, but not yet be destructed!
		}
		else {
			iter->get()->TickInternal(deltaTime);
			++iter;//it also need to increase the iterator
		}*/
	}

	//Update and draw the current stage 
	if (mCurrentStageIter != mGameStages.end()) {
		mCurrentStageIter->get()->TickStage(deltaTime);
	}
	
	Tick(deltaTime);
}

void ly::World::Tick(float deltaTime)
{
	//LOG_INFO(mlogger, "Ticking at {}", 1.f/ deltaTime);
}

void ly::World::InitGameStages()
{
}

void ly::World::NextGameStage()
{
	mCurrentStageIter = mGameStages.erase(mCurrentStageIter);
	if (mCurrentStageIter != mGameStages.end()) {
		mCurrentStageIter->get()->StartStage();
		mCurrentStageIter->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
	}
	else {
		AllGameStageFinished();
	}
}

void ly::World::AllGameStageFinished()
{
	LOG_INFO(mlogger, "All Stage is finished!");
}

void ly::World::StartStages()
{
	mCurrentStageIter = mGameStages.begin();
	mCurrentStageIter->get()->StartStage();
	mCurrentStageIter->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
}

void ly::World::BeginPlay()
{
	LOG_INFO(mlogger, "World begin play!");
}

void ly::World::CleanCycle()
{
	for (auto iter = mActors.begin(); iter != mActors.end();) {
		if (iter->get()->IsPendingDestory()) {
			iter = mActors.erase(iter);
		}
		else {
			++iter;//it also need to increase the iterator
		}
	}
	//cleaning the game stage here
	/* This will not work for multiple stage
	for (auto iter = mGameStages.begin(); iter != mGameStages.end();) {
		if (iter->get()->IsStageFininshed()) {
			iter = mGameStages.erase(iter);
		}
		else {
			++iter;//it also need to increase the iterator
		}
	}*/
}

void ly::World::AddGameStage(const shared<GameStage>& newStage)
{
	mGameStages.push_back(newStage);
}





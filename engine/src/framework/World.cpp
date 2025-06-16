#include "framework/World.h"
#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/sinks/ConsoleSink.h>

ly::World::World(Application* ptrOwner)
	:mPtrOwner{ ptrOwner }, mBeginPlay{false}
{
	mlogger = quill::Frontend::create_or_get_logger("world", quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1"));
	mlogger->set_immediate_flush(true);
}

ly::World::~World()
{
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
	Tick(deltaTime);
}

void ly::World::Tick(float deltaTime)
{
	LOG_INFO(mlogger, "Ticking at {}", 1.f/ deltaTime);
}

void ly::World::BeginPlay()
{
	LOG_INFO(mlogger, "World begin play!");
}





#include "framework/Actor.h"
#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/sinks/ConsoleSink.h>

ly::Actor::Actor(World* ptrOwner)
	:mPtrOwner{ ptrOwner },
	mIsBeginPlay{false}
{
	mlogger = quill::Frontend::create_or_get_logger("Actor", quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1"));
	mlogger->set_immediate_flush(true);
}

void ly::Actor::BeginPlayInternal()
{
	if (!mIsBeginPlay) {
		mIsBeginPlay = true;
		BeginPlay();
	}
}

void ly::Actor::BeginPlay()
{
	LOG_INFO(mlogger, "Begin play!");
}

void ly::Actor::Tick(float deltaTime)
{
	LOG_INFO(mlogger, "Ticking at {}", 1.f / deltaTime);
}

ly::Actor::~Actor()
{
}

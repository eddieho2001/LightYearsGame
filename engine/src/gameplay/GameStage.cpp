#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/sinks/ConsoleSink.h>

#include "gameplay/GameStage.h"
#include "framework/World.h"

ly::GameStage::GameStage(World* world)
	:mWorld{ world }, 
	mStageFinished{ false }
{
	mlogger = quill::Frontend::create_or_get_logger("GameStage", quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1"));
	mlogger->set_immediate_flush(true);
}

void ly::GameStage::StartStage()
{
	LOG_INFO(mlogger, "Stage Start!");
}

void ly::GameStage::TickStage(float deltaTime)
{
	LOG_INFO(mlogger, "Stage Tick{}", deltaTime);
}

void ly::GameStage::FinishStage()
{
	LOG_INFO(mlogger, "Stage Finish...");
	onStageFinished.Broadcast();
	mStageFinished = true;
	StageFinished();
}

void ly::GameStage::StageFinished()
{
	LOG_INFO(mlogger, "Stage Finished!");

}

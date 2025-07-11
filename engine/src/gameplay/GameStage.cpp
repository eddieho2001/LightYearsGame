#include "gameplay/GameStage.h"
#include "framework/World.h"

ly::GameStage::GameStage(World* world)
	:mWorld{ world }, 
	mStageFinished{ false }
{
}

#include "gameplay/WaitStage.h"
#include "framework/TimerManager.h"

ly::WaitStage::WaitStage(World* world, float waitDuration)
	:GameStage{world},
	mWaitDuration{waitDuration}
{
}

void ly::WaitStage::StartStage()
{
	TimerManager::GetInstance().SetTimer(GetWeakRef(), &WaitStage::FinishStage, mWaitDuration);
}


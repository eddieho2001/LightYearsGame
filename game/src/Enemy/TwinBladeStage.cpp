#include "framework/World.h"
#include "Enemy/TwinBladeStage.h"
#include "framework/TimerManager.h"
#include "Enemy/TwinBlade.h"

ly::TwinBladeStage::TwinBladeStage(World* world)
	:GameStage{ world },
	mSpawnInterval{ 1.5f },
	mSpawnDistanceToCenter{ 100.f },
	mSpawnAmt{ 10 },
	mCurrentSpawnCount{ 0 },
	mLeftSpawnLoc{ world->GetWindowSize().x/2.f - mSpawnDistanceToCenter, -100.f },
	mRightSpawnLoc{ world->GetWindowSize().x/2.f + mSpawnDistanceToCenter, -100.f },
	mSpawnLoc { mLeftSpawnLoc }
{
}

void ly::TwinBladeStage::StartStage()
{
	mSpawnTimerHandle = TimerManager::GetInstance().SetTimer(GetWeakRef(), &TwinBladeStage::SpawnTwinBlade, mSpawnInterval, true);
}

void ly::TwinBladeStage::SpawnTwinBlade()
{
	weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActors<TwinBlade>();
	newTwinBlade.lock()->SetLocation(mSpawnLoc);
	if (mSpawnLoc == mLeftSpawnLoc) {
		mSpawnLoc = mRightSpawnLoc;
	}
	else {
		mSpawnLoc = mLeftSpawnLoc;
	}

	++mCurrentSpawnCount;
	if (mCurrentSpawnCount == mSpawnAmt) {
		FinishStage();
	}
}

void ly::TwinBladeStage::StageFinished()
{
	TimerManager::GetInstance().CleanTimer(mSpawnTimerHandle);
}

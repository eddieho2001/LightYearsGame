#include "Enemy/VanguardStage.h"
#include "framework/World.h"
#include "Enemy/Vanguard.h"
#include "Enemy/TwinBlade.h"
#include "Enemy/Hexagon.h"

ly::VanguardStage::VanguardStage(World* world)
	: GameStage{ world },
	mSpawnInterval{ 2.f},
	mSwitchInterval{ 6.f },
	mSpawnDistanceToEdge{ 100.f },
	mRowsToSpawn{ 4 },
	mRowSpawnCount{ 0 },
	mVarguardsPerRow{ 5 },
	mCurrentRowVanguardCount{ 0 },
	mLeftSpawnLoc{0.0f, 0.0f},
	mRightSpawnLoc{0.0f, 0.0f},
	mSpawnLoc{0.0f, 0.0f},
	mSpawnTimerHdr{},
	mSwitchTimerHdr{}
{
}

void ly::VanguardStage::StartStage()
{
	auto winSize = GetWorld()->GetWindowSize();
	mLeftSpawnLoc = sf::Vector2f{ mSpawnDistanceToEdge , -100.f };
	mRightSpawnLoc = sf::Vector2f{ winSize.x - mSpawnDistanceToEdge, -100.f };
	SwitchRow();
}

void ly::VanguardStage::StageFinished()
{
	TimerManager::GetInstance().CleanTimer(mSpawnTimerHdr);
	TimerManager::GetInstance().CleanTimer(mSwitchTimerHdr);
}

void ly::VanguardStage::SpawnVanguard()
{
	//weak<Vanguard> newVanguard = GetWorld()->SpawnActors<Vanguard>();
	weak<Hexagon> newVanguard = GetWorld()->SpawnActors<Hexagon>();
	newVanguard.lock()->SetLocation(mSpawnLoc);
	++mCurrentRowVanguardCount;
	if (mCurrentRowVanguardCount == mVarguardsPerRow) {
		TimerManager::GetInstance().CleanTimer(mSpawnTimerHdr);
		mSwitchTimerHdr = TimerManager::GetInstance().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, mSwitchInterval, false);
		mCurrentRowVanguardCount = 0;//if not reset, it canot switch
	}
}

void ly::VanguardStage::SwitchRow()
{
	if (mRowSpawnCount == mRowsToSpawn) {
		FinishStage();
		return;
	}

	if (mSpawnLoc == mLeftSpawnLoc) {
		mSpawnLoc = mRightSpawnLoc;
	}
	else {
		mSpawnLoc = mLeftSpawnLoc;
	}

	mSpawnTimerHdr = TimerManager::GetInstance().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);
	++mRowSpawnCount;
}

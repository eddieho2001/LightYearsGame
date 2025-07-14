#pragma once

#include <SFML/Graphics.hpp>
#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly {
	class World;
	class VanguardStage: public GameStage{
	public:
		VanguardStage(World* world);
		virtual void StartStage() override;
	private:
		virtual void StageFinished() override;
		void SpawnVanguard();
		void SwitchRow();
	private:
		float mSpawnInterval;
		float mSwitchInterval;
		float mSpawnDistanceToEdge;
		sf::Vector2f mLeftSpawnLoc;
		sf::Vector2f mRightSpawnLoc;
		sf::Vector2f mSpawnLoc;

		TimerHandler mSpawnTimerHdr;
		TimerHandler mSwitchTimerHdr;

		int mRowsToSpawn;
		int mRowSpawnCount;
		int mVarguardsPerRow;
		int mCurrentRowVanguardCount;
	};
}
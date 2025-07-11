#pragma once

#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly {
	class World;
	class GameStage : public Object {
	public:
		GameStage(World* world);
		const World* GetWorld() const { return mWorld; }
		World* GetWorld() { return mWorld; }
		virtual void StartStage();
		virtual void TickStage(float deltaTime);
		
		void FinishStage();
		bool IsStageFininshed() const { return mStageFinished; }
	private:
		virtual void StageFinished();
	private:
		World* mWorld;
		bool mStageFinished;


	};

}
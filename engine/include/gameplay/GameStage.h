#pragma once
#include<quill/Logger.h>
#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly {
	class World;//world will responsible for manage Stages 
	class GameStage : public Object {
	public:
		GameStage(World* world);
		const World* GetWorld() const { return mWorld; }
		World* GetWorld() { return mWorld; }
		virtual void StartStage();
		virtual void TickStage(float deltaTime);
		
		void FinishStage();
		bool IsStageFininshed() const { return mStageFinished; }

		Delegate<> onStageFinished;
	private:
		virtual void StageFinished();
	private:
		World* mWorld;
		bool mStageFinished;
		quill::Logger* mlogger;

	};

}
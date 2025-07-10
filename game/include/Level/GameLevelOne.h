#pragma once

#include<quill/Logger.h>
#include "framework/World.h"
#include "framework/Core.h"

namespace ly {
	//class Application;
	class PlayerSpaceship;
	class GameLevelOne : public World {
	public:
		GameLevelOne(Application* owner);
	private:
		virtual void BeginPlay() override;
		//Because we need to use TimerManager to set timer do something, we need to implement callback function here
		void TimerCallback();
	private:
		//Application* mPtrOwner;
		weak<PlayerSpaceship> mTestPlayeSpaceship;
		quill::Logger* mlogger;
		unsigned int timerIdx;
	};
}
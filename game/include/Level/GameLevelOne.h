#pragma once
#include "framework/World.h"
#include "framework/Core.h"

namespace ly {
	//class Application;
	class PlayerSpaceship;
	class GameLevelOne : public World {
	public:
		GameLevelOne(Application* owner);
	private:
		//Application* mPtrOwner;
		weak<PlayerSpaceship> mTestPlayeSpaceship;
	};
}
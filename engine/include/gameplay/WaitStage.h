#pragma once

#include "gameplay/GameStage.h"

namespace ly {
	class WaitStage : public GameStage {
	public:
		WaitStage(World* world, float waitDuration = 5.0f);
		virtual void StartStage() override;
	private:
		float mWaitDuration;
	};
}
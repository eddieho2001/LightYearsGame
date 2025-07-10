#pragma once

#include<functional>

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly {

	struct Timer{
	public:
		Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat);
		void TickTime(float deltaTime);
		bool Expired() const;
		void SetExpired();
	private:
		std::pair<weak<Object>, std::function<void()>> listenerPair;
		float mDuration;
		bool mIsRepeat;
		float mTimeCounter;
		bool mIsExpired;
	};

	class TimerManager {
	public:
		static TimerManager& GetInstance();
		template<typename ClassName>
		unsigned int SetTimer(weak<Object> weakRef, void(ClassName::* callback)(), float duration, bool repeat = false) {
			timerIndex++;
			mTimers.insert({ timerIndex, Timer(weakRef, [=] {(static_cast<ClassName*>(weakRef.lock().get())->*callback)(); }, duration, repeat) });
			return timerIndex;
		}

		void UpdateTimer(float deltaTime);
		void CleanTimer(unsigned int timerIdx);
	protected:
		TimerManager();
	private:
		static unique<TimerManager> mTimerMgr;
		static unsigned int timerIndex;
		Dictionary<int, Timer> mTimers;
	};
}
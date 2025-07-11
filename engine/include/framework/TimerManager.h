#pragma once

#include<functional>

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly {
	struct TimerHandler {
	public:
		TimerHandler();
		unsigned int GetTimerKey() const { return mTimerKey; };
	private:
		static unsigned int GetNextTimerKey() { return timerKeyCounter++; };
	private:
		unsigned int mTimerKey;
		static unsigned int timerKeyCounter;
	};

	struct TimerHandleHasher {
	public:
		std::size_t operator()(const TimerHandler& handler) const {
			return handler.GetTimerKey();
		}
	};

	bool operator==(const TimerHandler& lhs, const TimerHandler& rhs);

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
		TimerHandler SetTimer(weak<Object> weakRef, void(ClassName::* callback)(), float duration, bool repeat = false) {
			TimerHandler newHandler{};
			mTimers.insert({ newHandler, Timer(weakRef, [=] {(static_cast<ClassName*>(weakRef.lock().get())->*callback)(); }, duration, repeat) });
			return newHandler;
		}

		void UpdateTimer(float deltaTime);
		void CleanTimer(TimerHandler timerHandler);
	protected:
		TimerManager();
	private:
		static unique<TimerManager> mTimerMgr;
		
		//Note the key is customed object, the map don't know how to compare the key customed object, we need to teach map how to compare them!
		Dictionary<TimerHandler, Timer, TimerHandleHasher> mTimers;
	};
}
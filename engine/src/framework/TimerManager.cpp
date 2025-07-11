#include "framework/TimerManager.h"

namespace ly {
	//Because it is static, we nned to initialized it before use.
	unique<TimerManager> ly::TimerManager::mTimerMgr{ nullptr };
	unsigned int TimerHandler::timerKeyCounter = 0;

	bool operator==(const TimerHandler& lhs, const TimerHandler& rhs) {
		return lhs.GetTimerKey() == rhs.GetTimerKey();
	}

	TimerManager& TimerManager::GetInstance()
	{
		if (!mTimerMgr) {
			mTimerMgr = std::move(unique<TimerManager>{ new TimerManager });
		}

		return *mTimerMgr;
	}

	void TimerManager::UpdateTimer(float deltaTime)
	{
		//iterate a map
		for (auto iter = mTimers.begin(); iter != mTimers.end();) {
			if (iter->second.Expired()) {   //check it is expired and remove from map
				iter = mTimers.erase(iter);
			}
			else {
				iter->second.TickTime(deltaTime);
				iter++;
			}
		}
		/*
		for (Timer& timer : mTimers) {
			timer.TickTime(deltaTime);
		}*/
	}

	void TimerManager::CleanTimer(TimerHandler timerHandler)
	{
		auto iter = mTimers.find(timerHandler);
		if (iter != mTimers.end()) {
			iter->second.SetExpired();//set the timer expired
		}
	}

	ly::TimerManager::TimerManager()
		:mTimers{}
	{

	}

	Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat):
		listenerPair{ weakRef ,callback},
		mDuration{ duration },
		mIsRepeat{ repeat },
		mTimeCounter{0.f},
		mIsExpired{false}
	{
	}

	void Timer::TickTime(float deltaTime)
	{
		if (!Expired()) {
			mTimeCounter += deltaTime;
			//check the time is or not reach the duration
			if (mTimeCounter >= mDuration) {
				//call the callback function
				listenerPair.second();//call the timer's callback action here!

				if (mIsRepeat) {
					mTimeCounter = 0.f;
				}
				else {
					SetExpired();
				}
			}
		}
	}

	bool Timer::Expired() const
	{
		return mIsExpired || listenerPair.first.expired() || listenerPair.first.lock()->IsPendingDestory();
	}

	void Timer::SetExpired()
	{
		mIsExpired = true;
	}

	TimerHandler::TimerHandler()
		:mTimerKey{ GetNextTimerKey() }
	{
	}

}
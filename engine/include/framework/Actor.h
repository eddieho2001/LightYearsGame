#pragma once
#include<quill/Logger.h>

namespace ly {
	/*
	 * The Actor class's owner is the World class. 
	 */
	class World;
	class Actor {
	public:
		Actor(World* ptrOwner);
		void BeginPlayInternal();
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual ~Actor();
	private:
		World* mPtrOwner;
		bool mIsBeginPlay;
		quill::Logger* mlogger;
	};
}
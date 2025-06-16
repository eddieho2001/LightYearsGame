#pragma once
#include "framework/application.h"
#include<quill/Logger.h>

namespace ly {
	/* 
	 * The world class represent the level, similar to Unreal engine world concept.
	 * The owner of the World is Application class as it parent class.
	 * 1 ) The basic for the class is set it begin
	 * 2 ) Implement the tick function
	 */
	class Application; //forward declaration
	class World {
	public:
		World(Application* ptrOwner);
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		virtual ~World();
	private:
		void BeginPlay();
		void Tick(float deltaTime);
	private:
		Application *mPtrOwner;
		bool mBeginPlay;
		quill::Logger* mlogger;

	};
}
#pragma once
#include "framework/application.h"
#include "framework/Core.h"

#include<quill/Logger.h>

namespace ly {
	/* 
	 * The world class represent the level, similar to Unreal engine world concept.
	 * The owner of the World is Application class as it parent class.
	 * 1 ) The basic for the class is set it begin
	 * 2 ) Implement the tick function
	 * 3 ) It manage a two set of lifetime of Actor class
	 * 4 ) The Actor inheritacne from Object so that World class can manage the Actor lifetime
	     
	 */
	class Application; //forward declaration
	class Actor;
	class World {
	public:
		World(Application* ptrOwner);
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		virtual ~World();
		void Render(sf::RenderWindow& win);

		template<typename actorType>
		weak<actorType> SpawnActors();

	private:
		void BeginPlay();
		void Tick(float deltaTime);
	private:
		Application *mPtrOwner;
		bool mBeginPlay;
		List<shared<Actor> > mActors;
		List<shared<Actor> > mPendingActors;
		quill::Logger* mlogger;

	};

	template<typename actorType>
	weak<actorType> World::SpawnActors() {
		shared<actorType> newActor{ new actorType{this} };
		mPendingActors.push_back(newActor);
		return newActor;
	}
}
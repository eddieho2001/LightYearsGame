#pragma once
#include "framework/application.h"
#include "framework/Core.h"
#include "framework/Object.h"

#include<quill/Logger.h>

namespace ly {
	/* 
	 * The world class represent the level, similar to Unreal engine world concept.
	 * The owner of the World is Application class as it parent class.
	 * 1 ) The basic for the class is set it begin
	 * 2 ) Implement the tick function
	 * 3 ) It manage a two set of lifetime of Actor class
	 * 4 ) The Actor inheritacne from Object so that World class can manage the Actor lifetime
	 *    
	 */
	class Application; //forward declaration
	class Actor;
	class GameStage;
	class World : public Object{
	public:
		World(Application* ptrOwner);
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		virtual ~World();
		void Render(sf::RenderWindow& win);

		//Handle the Bullet, it need to change it
		template<typename actorType, typename... Args>
		weak<actorType> SpawnActors(Args... args);

		sf::Vector2u GetWindowSize() const { return mPtrOwner->GetWinowSize(); }

		//Add CleanCycle for clean usage actor type under the world
		void CleanCycle();

		//Add game stage to world
		void AddGameStage(const shared<GameStage>& newStage);

	private:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void InitGameStages();
		void NextGameStage();
		virtual void AllGameStageFinished();
		void StartStages();
	private:
		Application *mPtrOwner;
		bool mBeginPlay;
		List<shared<Actor> > mActors;
		List<shared<Actor> > mPendingActors;
		quill::Logger* mlogger;

		//Using shared pointer because we need to use delegate & timer 
		List<shared<GameStage>> mGameStages;
		//Because if multiple stage, we cannot clean it just by index
		//int mCurrentStageIdx;
		//We use conatiner's iterator
		List<shared<GameStage>>::iterator mCurrentStageIter;
	};

	template<typename actorType, typename... Args>
	weak<actorType> World::SpawnActors(Args... args) {
		shared<actorType> newActor{ new actorType(this, args...) };
		mPendingActors.push_back(newActor);
		return newActor;
	}
}
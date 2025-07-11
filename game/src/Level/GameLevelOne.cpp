#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/sinks/ConsoleSink.h>

#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "framework/Actor.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"
#include "framework/TimerManager.h"

ly::GameLevelOne::GameLevelOne(Application* owner)
	:World{ owner }
{
	mlogger = quill::Frontend::create_or_get_logger("GameLevelOne", quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1"));
	mlogger->set_immediate_flush(true);

	mTestPlayeSpaceship = SpawnActors<PlayerSpaceship>();
	mTestPlayeSpaceship.lock()->SetLocation(sf::Vector2f(600 / 2, 980 / 2));
	
	weak<Vanguard> testSpacesship = SpawnActors<Vanguard>();
	testSpacesship.lock()->SetLocation(sf::Vector2f{ 100.f, 50.f });
	// we cannot call the TimerManager::GetInstance() because the World ctor not yet finish!
}

void ly::GameLevelOne::BeginPlay()
{
	timerHandler = TimerManager::GetInstance().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallback, 3, true);
}

void ly::GameLevelOne::TimerCallback()
{
	TimerManager::GetInstance().CleanTimer(timerHandler);
	LOG_INFO(mlogger, "Test: Timer Callback & Clean Timer handler :{}", timerHandler.GetTimerKey());
}

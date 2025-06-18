#include "framework/application.h"
#include "framework/World.h"
#include "framework/AssetManager.h"

#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/sinks/ConsoleSink.h>

//const float ly::Application::PlayerSpeed = 100.f;
//const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

ly::Application::Application(unsigned int winWidth, unsigned int winHeight, const std::string& title, sf::Uint32 style)
	: mWindow{ sf::VideoMode(winWidth, winHeight), title,  style },
	  mTargetFrameRate{60.f},//if 60 frame/s, i.e. is one frame is 0.01666666 second
	  mTickClock{},
	  currentWorld{nullptr},
	  mCleanCycleClock{},
	  mCleanCycleInterval{2.f}
{

	mlogger = quill::Frontend::create_or_get_logger("App", quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1"));
	mlogger->set_immediate_flush(true);
	/*
	if (!mTexture.loadFromFile("D:/MyDocs/GameDev/Udemy/LearnC++AndMakeaGameFromScratch/Section06/LightYearsGame/Eagle.png")) {
		//std::cout << "Load error!" << std::endl;
		LOG_ERROR(mlogger, "Loading image error for Texture!");
	}
	else {
		mPlayer.setTexture(mTexture);
		mPlayer.setPosition(100.f, 100.f);
	}
	*/
}

void ly::Application::Run() {
	//The game loop: An iteration of the game loop is often call frame/tick
	//Frame per Second(FPS) - A measurement of how many loops iteration the game can do during a second.  
	
	//In order to solve frame-dependent: because the physics engine require a fixed time constant to calculate many physic quantity
	//Add a clock to measure time for each frame take
	//sf::Clock clock;
	//sf::Time timeSinceLastUpdate = sf::Time::Zero;
	//--------------------------------
	mTickClock.restart();
	float accumulatedTime{ 0.f };
	float targetDeltaTime{ 1.f / mTargetFrameRate }; //=0.016666666s
	while (mWindow.isOpen())
	{
		//call three handler to processing tasks
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			//Handling events incoming
			if (event.type == sf::Event::Closed) {
				mWindow.close();
			}
		}
		

		float frameDeltaTime = mTickClock.restart().asSeconds();
		//accumulatedTime += mTickClock.restart().asSeconds();
		accumulatedTime += frameDeltaTime;
		//check if the accumulatedTime > targetDeltaTime(0.0166666s), perform update
		while (accumulatedTime > targetDeltaTime) {
			/*
				why do that because if there are the slow machine, each delta time itself is greater than the targetDeltaTime, 
				if greater than twice the inner while loop will update it twice. 
			*/
			accumulatedTime -= targetDeltaTime;
			//processEvents();
			//sf::Time delta = sf::seconds(targetDeltaTime);
			TickInternal(targetDeltaTime);
			RenderInternal();
		}

		//LOG_INFO(mlogger, "Tick for real frame rate : {}", 1.f / frameDeltaTime);
	}
}

void ly::Application::TickInternal(float deltaTime) {
	Tick(deltaTime);
	if (currentWorld) {
		currentWorld->TickInternal(deltaTime);
	}

	//call asset manager check and clean resource
	if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval) {
		//Reset the clock and ask asset manager to clean
		mCleanCycleClock.restart();
		AssetManager::GetInstance().CleanCycle();
	}
}

/*
void ly::Application::processEvents() {
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		//Handling events incoming
		
		if (event.type == sf::Event::Closed)
			mWindow.close();
		
		//It need pair of event, because first is activate, the second is deactivate
		switch (event.type) {
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}

	}
}

void ly::Application::TickInternal(sf::Time& deltaTime) {
	if (currentWorld) {
		Tick(deltaTime.asSeconds());
		currentWorld->TickInternal(deltaTime.asSeconds());
	}
	else {

		sf::Vector2f movement{ 0.f, 0.f };
		if (mIsMovingUp)
			movement.y -= PlayerSpeed;
		if (mIsMovingDown)
			movement.y += PlayerSpeed;
		if (mIsMovingLeft)
			movement.x -= PlayerSpeed;
		if (mIsMovingRight)
			movement.x += PlayerSpeed;
		Tick(movement * deltaTime.asSeconds());
	}
}

void ly::Application::Tick(sf::Vector2f& movement) {
	mPlayer.move(movement);
}
*/

void ly::Application::Tick(float deltaTime) {

}

void ly::Application::RenderInternal() {
	mWindow.clear();
	Render();
	mWindow.display();
}

void ly::Application::Render() {
	
	//The application contains world, we delegate it to actors class that in the world to draw itself!
	if (currentWorld) {
		currentWorld->Render(mWindow);
	}
	
}

/*
void ly::Application::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up) {
		mIsMovingUp = isPressed;
	}
	else if (key == sf::Keyboard::Down) {
		mIsMovingDown = isPressed;
	}
	else if (key == sf::Keyboard::Left) {
		mIsMovingLeft = isPressed;
	}
	else if (key == sf::Keyboard::Right) {
		mIsMovingRight = isPressed;
	}
	
}
*/

#include "framework/application.h"
#include "framework/World.h"
#include <iostream>

const float ly::Application::PlayerSpeed = 100.f;
//const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

ly::Application::Application()
	: mWindow{ sf::VideoMode(640, 480), "SFML Application" },
	  mPlayer{},
	  mTexture{},
	  mIsMovingUp{ false }, 
	  mIsMovingDown{ false }, 
	  mIsMovingLeft{ false }, 
	  mIsMovingRight{false},
	  mTargetFrameRate{60.f},//if 60 frame/s, i.e. is one frame is 0.01666666 second
	  mTickClock{},
	  currentWorld{nullptr}
{

	if (!mTexture.loadFromFile("D:/MyDocs/GameDev/Udemy/LearnC++AndMakeaGameFromScratch/Section06/LightYearsGame/Eagle.png")) {
		std::cout << "Load error!" << std::endl;
	}
	else {
		mPlayer.setTexture(mTexture);
		mPlayer.setPosition(100.f, 100.f);
	}
	
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
		/*
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			//Handling events incoming
			if (event.type == sf::Event::Closed) {
				mWindow.close();
			}
		}
		*/

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
			processEvents();
			sf::Time delta = sf::seconds(targetDeltaTime);
			TickInternal(delta);
			RenderInternal();
		}

		std::cout << "Tick for real frame rate : " << 1.f / frameDeltaTime << std::endl;
		
	}
}

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
	std::cout << "Tick at frame rate : " << 1.f / deltaTime.asSeconds() << std::endl;
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

void ly::Application::Tick(sf::Vector2f& movement) {
	mPlayer.move(movement);
}

void ly::Application::Tick(float deltaTime) {

}

void ly::Application::RenderInternal() {
	mWindow.clear();
	Render();
	mWindow.display();
}

void ly::Application::Render() {
	
	mWindow.draw(mPlayer);
	
}

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

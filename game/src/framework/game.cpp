#include "framework/game.h"
#include <iostream>

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow{ sf::VideoMode(640, 480), "SFML Application" },
	  mPlayer{}, 
	  mIsMovingUp{ false }, 
	  mIsMovingDown{ false }, 
	  mIsMovingLeft{ false }, 
	  mIsMovingRight{false}
{
	mPlayer.setRadius(40.f);
	mPlayer.setPosition(100.f, 100.f);
	mPlayer.setFillColor(sf::Color::Cyan);
}

void Game::run() {
	//The game loop: An iteration of the game loop is often call frame/tick
	//Frame per Second(FPS) - A measurement of how many loops iteration the game can do during a second.  
	
	//In order to solve frame-dependent: because the physics engine require a fixed time constant to calculate many physic quantity
	//Add a clock to measure time for each frame take
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		//call three handler to processing tasks
		sf::Time elapsedTime = clock.restart();//return the elapsed timesince it start, and retart the clock from zero
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		//processEvents();
		
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		//Handling events incoming
		/*
		if (event.type == sf::Event::Closed)
			mWindow.close();
		*/
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

		std::cout << "mIsMovingUp=" << mIsMovingUp << ", mIsMovingDown=" << mIsMovingDown << ", mIsMovingLeft=" << mIsMovingLeft << ", mIsMovingRight=" << mIsMovingRight << std::endl;
	}
}


/* 
 *	Because the update is frame-dependent(i.e. it depend on the time frame)
 *  In order to solve it we can apply the formula d = speed * time (delta time)
 */
void Game::update(sf::Time deltaTime) {
	sf::Vector2f movement{ 0.f, 0.f };
	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

	mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::render() {
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
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

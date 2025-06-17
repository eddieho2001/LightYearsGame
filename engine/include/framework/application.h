#pragma once
#include<SFML/Graphics.hpp>
#include<quill/Logger.h>
#include "framework/Core.h"

/* 
 *  The class Application represent the whole game. 
 *  The class take the main function and divide them into three main parts
 */
//
namespace ly{
	class World;
	class Application {
	public:
		Application();
		void Run();//Handle the game loop

		/*
		 * The template function create World object and return it as weak pointer, because the caller should not have the object ownership
		 * The ownership is Application object!
		 */
		template<typename worldType>
		weak<worldType> LoadWorld(){
			shared<worldType> newWorld{ new worldType{this} };
			currentWorld = newWorld;
			currentWorld->BeginPlayInternal();
			return newWorld;
		}

	private:
		//There are three necessary parts in game loop :  
		void processEvents(); //1. Handle events
		//void update(sf::Time& deltaTime);        //2. Update game state 
		void TickInternal(sf::Time& deltaTime);
		virtual void Tick(sf::Vector2f& movement);
		virtual void Tick(float deltaTime);

		void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
		
		virtual void Render();        //3. draw the changed on screen  
		void RenderInternal();

	private:
		sf::RenderWindow mWindow;
		sf::Sprite mPlayer;
		sf::Texture mTexture;
		static const float PlayerSpeed;
		//static const sf::Time TimePerFrame;
		bool mIsMovingUp;
		bool mIsMovingDown;
		bool mIsMovingLeft;
		bool mIsMovingRight;
		//The number of cycle as per second we will looking for
		float mTargetFrameRate;
		sf::Clock mTickClock;
		quill::Logger* mlogger;

		shared<World> currentWorld;
	};
}
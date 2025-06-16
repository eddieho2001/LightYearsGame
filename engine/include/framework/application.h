#pragma once
#include<SFML/Graphics.hpp>
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

		//The template function create World and return it shared pointer
		template<typename worldType>
		weak<worldType> RoadWorld(){
			shared<worldType> newWorld{ new worldType{this} };
			currentWorld = newWorld;
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
		//sf::CircleShape mPlayer;
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

		shared<World> currentWorld;
	};
}
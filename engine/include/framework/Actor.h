#pragma once
#include<quill/Logger.h>
#include "framework/Object.h"
#include<SFML/Graphics.hpp>
#include "framework/Core.h"


namespace ly {
	/*
	 * The Actor class's owner is the World class.
	   It has visual component Sprite(visual and transformable(means can move)
	 */
	class World;
	class Actor : public Object{
	public:
		Actor(World* ptrOwner, const std::string& texturePath="");
		void BeginPlayInternal();
		virtual void BeginPlay();
		void TickInternal(float deltaTime);
		virtual void Tick(float deltaTime);
		virtual ~Actor();
		void SetTexture(const std::string& path);
		void Render(sf::RenderWindow& win);
	private:
		World* mPtrOwner;
		bool mIsBeginPlay;
		quill::Logger* mlogger;
		//Start to add visual component here 
		sf::Sprite mSprite;
		shared<sf::Texture> mTexture;
	};
}
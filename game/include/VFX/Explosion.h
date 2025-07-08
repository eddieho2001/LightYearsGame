#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include "framework/Core.h"

namespace ly {
	class World;
	class Explosion {
	public:
		Explosion(int particleAmt = 20, 
				  float minSpeed = 200.f, 
				  float maxSpeed = 400.f, 
				  float minSize  = 1.f, 
			      float maxSize  = 3.f, 
				  float minLifeTime = 0.5f, 
			      float maxLifeTime = 1.5f,
				  const sf::Color& particleColor = sf::Color{255,128,0, 255},
				  const List<std::string>& particleImgPaths = {
						"SpaceShooterRedux/PNG/Effects/star1.png",
						"SpaceShooterRedux/PNG/Effects/star2.png",
						"SpaceShooterRedux/PNG/Effects/star3.png"
				  });

		void SpawnExplosion(World* ptrWorld, const sf::Vector2f& loc);
	private:
		int mParticleAmt;
		List<std::string> mListParticleImgPath;
		float mMinSpeed;
		float mMaxSpeed;
		float mMinSize;
		float mMaxSize;
		float mMinLifeTime;
		float mMaxLifeTime;
		sf::Color mParticleColor;
	};
}
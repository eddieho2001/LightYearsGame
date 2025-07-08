#include "VFX/Explosion.h"
#include "framework/MathUtility.h"
#include "VFX/Particle.h"
#include "framework/World.h"

ly::Explosion::Explosion(int particleAmt, 
		float minSpeed, 
		float maxSpeed, 
		float minSize, 
		float maxSize, 
		float minLifeTime, 
		float maxLifeTime, 
	    const sf::Color& particleColor,
		const List<std::string>& particleImgPaths)
	 :mParticleAmt{ particleAmt },
	 mMinSpeed{ minSpeed },
	 mMaxSpeed{ maxSpeed },
	 mMinSize{ minSize },
	 mMaxSize{ maxSize },
	 mMinLifeTime{ minLifeTime },
	 mMaxLifeTime{ maxLifeTime },
	 mParticleColor{ particleColor },
	 mListParticleImgPath{ particleImgPaths }
{
}

void ly::Explosion::SpawnExplosion(World* ptrWorld, const sf::Vector2f& loc)
{
	if (ptrWorld) {
		for (int i{ 0 }; i < mParticleAmt; i++) {
			std::string particleImgPath = mListParticleImgPath[static_cast<int>(RandomRange(0, mListParticleImgPath.size()))];
			weak<Particle> newParticle = ptrWorld->SpawnActors<Particle>(particleImgPath);
			newParticle.lock()->RandomLiftTime(mMinLifeTime, mMaxLifeTime);
			newParticle.lock()->SetLocation(loc);
			newParticle.lock()->RandomSize(mMinSize, mMaxSize);
			newParticle.lock()->RandomVelocity(mMinSpeed, mMaxSpeed);
			newParticle.lock()->GetSprite().setColor(mParticleColor);
		}
	}
}

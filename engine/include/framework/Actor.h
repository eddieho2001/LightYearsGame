#pragma once
#include<quill/Logger.h>
#include "framework/Object.h"
#include<SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/MathUtility.h"

class b2Body;
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
		void SetLocation(const sf::Vector2f& newLocaltion);
		sf::Vector2f GetLocation() const;
		void SetRotation(float newRotation);
		float GetRotataion() const;
		void AddLocationOffset(const sf::Vector2f& offset);
		void AddRotationOffset(float offset);
		
		sf::Vector2f GetRightDirection() const;
		sf::Vector2f GetLeftDirection() const;
		sf::Vector2f GetForwardDirection() const;
		sf::Vector2u GetWindowSize() const { return mPtrOwner->GetWindowSize(); }
		bool IsOutOfWindowBound() const;
		sf::FloatRect GetGlobalBounds() const;

		World* GetWorld() const { return mPtrOwner; }

		void SetEnablePhysics(bool enable);
		virtual void OnActorBeginOverlap(Actor* other);
		virtual void OnActorEndOverlap(Actor* other);
		virtual void Destory() override;
		static uint8 GetNeturalTeamId() { return neturalTeamId; }
		bool IsOtherHostile(Actor* other) const;
		void SetTeamId(uint8 teamId) { mTeamId = teamId; }
		uint8 GetTeamId() const { return mTeamId; }
		virtual void ApplyDamage(float amt);
	private:
		void CenterPivot();
		void InitializedPhysics();
		void UnInitializedPhysics();
		void UpdatePhysicsBodyTransform();
	private:
		World* mPtrOwner;
		bool mIsBeginPlay;
		quill::Logger* mlogger;
		//Start to add visual component here 
		sf::Sprite mSprite;
		shared<sf::Texture> mTexture;
		b2Body* mPhysicsBody;
		bool mPhysicsEnabled;
		uint8 mTeamId;
	};
}
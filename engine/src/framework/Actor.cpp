#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/sinks/ConsoleSink.h>
#include<box2d/b2_body.h>

#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/PhysicsSystem.h"

ly::Actor::Actor(World* ptrOwner, const std::string& texturePath)
	:mPtrOwner{ ptrOwner },
	mIsBeginPlay{false},
	mPhysicsBody{nullptr},
	mPhysicsEnabled{false},
	mSprite{},
	mTexture{},
	mTeamId{ GetNeturalTeamId()}
{
	mlogger = quill::Frontend::create_or_get_logger("Actor", quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1"));
	mlogger->set_immediate_flush(true);
	SetTexture(texturePath);
}

void ly::Actor::BeginPlayInternal()
{
	if (!mIsBeginPlay) {
		mIsBeginPlay = true;
		BeginPlay();
	}
}

void ly::Actor::BeginPlay()
{
	LOG_INFO(mlogger, "Begin play!");
}

void ly::Actor::TickInternal(float deltaTime)
{
	if (!IsPendingDestory()) {
		Tick(deltaTime);
	}
}

void ly::Actor::Tick(float deltaTime)
{
	//LOG_INFO(mlogger, "Ticking at {}", 1.f / deltaTime);
}

ly::Actor::~Actor()
{
	//_LOG("Actor destoryed");
	LOG_INFO(mlogger, "Actor destoryed");
}

void ly::Actor::SetTexture(const std::string& path)
{
	//The GetInstance return static object, we use reference to hold it!
	//AssetManager& assetMgr = AssetManager::GetInstance();
	mTexture = AssetManager::GetInstance().LoadTexture(path);
	if (!mTexture) {
		LOG_ERROR(mlogger, "Cannot load image from path({})", path);
		return;
	}
	mSprite.setTexture(*mTexture);
	int tWidth = mTexture->getSize().x;
	int tHeight = mTexture->getSize().y;
	mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{tWidth, tHeight} });
	CenterPivot();
	/*
	if (!mTexture.loadFromFile(path)) {
		LOG_ERROR(mlogger, "Cannot load image from path({})", path);
	}
	else {
		mSprite.setTexture(mTexture);
		int tWidth = mTexture.getSize().x;
		int tHeight = mTexture.getSize().y;
		mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{tWidth, tHeight} });
	}*/
}

void ly::Actor::Render(sf::RenderWindow& win)
{
	if (IsPendingDestory()) {
		return;
	}

	win.draw(mSprite);
}

void ly::Actor::SetLocation(const sf::Vector2f& newLocaltion)
{
	mSprite.setPosition(newLocaltion);
	UpdatePhysicsBodyTransform();
}

sf::Vector2f ly::Actor::GetLocation() const
{
	return mSprite.getPosition();
}

void ly::Actor::SetRotation(float newRotation)
{
	mSprite.setRotation(newRotation);
	UpdatePhysicsBodyTransform();
}

float ly::Actor::GetRotataion() const
{
	return mSprite.getRotation();
}

void ly::Actor::AddLocationOffset(const sf::Vector2f& offset)
{
	SetLocation(GetLocation() + offset);
}

void ly::Actor::AddRotationOffset(float offset)
{
	SetRotation(GetRotataion() + offset);
}

sf::Vector2f ly::Actor::GetForwardDirection() const
{
	return Rotation2Vecor(GetRotataion());
}

sf::Vector2f ly::Actor::GetLeftDirection() const
{
	return Rotation2Vecor(GetRotataion() - 90.f);
}

sf::Vector2f ly::Actor::GetRightDirection() const
{
	return Rotation2Vecor(GetRotataion()+90.f);
}

void ly::Actor::CenterPivot()
{
	sf::FloatRect bound = mSprite.getGlobalBounds();
	mSprite.setOrigin(bound.width / 2, bound.height / 2);
}

bool ly::Actor::IsOutOfWindowBound() const
{
	//Find the world size first
	float gameWinWidth = GetWorld()->GetWindowSize().x;
	float gameWinHeight = GetWorld()->GetWindowSize().y;
	//Find the actor it size
	float actorWidth = GetGlobalBounds().width;
	float actorHeight = GetGlobalBounds().height;
	sf::Vector2f actorPos = GetLocation();
	
	if (actorPos.x < -actorWidth) {
		return true;
	}

	if (actorPos.x > (gameWinWidth + actorWidth)) {
		return true;
	}

	if (actorPos.y < -actorHeight) {
		return true;
	}

	if (actorPos.y > (gameWinHeight + actorHeight)) {
		return true;
	}

	return false;
}


sf::FloatRect ly::Actor::GetGlobalBounds() const
{
	return mSprite.getGlobalBounds();
}

void ly::Actor::SetEnablePhysics(bool enable)
{
	mPhysicsEnabled = enable;
	if (mPhysicsEnabled) {
		InitializedPhysics();
	}
	else {
		UnInitializedPhysics();
	}
}

void ly::Actor::OnActorBeginOverlap(Actor* other)
{
	//LOG_INFO(mlogger, "Acotr Beging Overlap");
}

void ly::Actor::OnActorEndOverlap(Actor* other)
{
	//LOG_INFO(mlogger, "Acotr End Overlap");
}

void ly::Actor::Destory()
{
	UnInitializedPhysics();
	Object::Destory();
}

void ly::Actor::InitializedPhysics()
{
	if (!mPhysicsBody) {
		mPhysicsBody = PhysicsSystem::GetInstance().AddListener(this);
	}
}

void ly::Actor::UnInitializedPhysics()
{
	if (mPhysicsBody) {
		PhysicsSystem::GetInstance().RemoveListener(mPhysicsBody);
		mPhysicsBody = nullptr;
	}
}

void ly::Actor::UpdatePhysicsBodyTransform()
{
	if (mPhysicsBody) {
		float physicsScale = PhysicsSystem::GetInstance().GetPhysicsScale();
		b2Vec2 pos{ physicsScale * GetLocation().x, physicsScale * GetLocation().y };
		float rotation = Degree2Radian(GetRotataion());
		mPhysicsBody->SetTransform(pos, rotation);
	}
}

bool ly::Actor::IsOtherHostile(Actor* other) const
{
	if (GetTeamId() == GetNeturalTeamId() || other->GetTeamId() == GetNeturalTeamId()) {
		return false;
	}
	return GetTeamId() != other->GetTeamId();
}

void ly::Actor::ApplyDamage(float amt)
{

}

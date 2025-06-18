#include "framework/Actor.h"
#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/sinks/ConsoleSink.h>
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"

ly::Actor::Actor(World* ptrOwner, const std::string& texturePath)
	:mPtrOwner{ ptrOwner },
	mIsBeginPlay{false},
	mSprite{},
	mTexture{}
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
	_LOG("Actor destoryed");
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
}

sf::Vector2f ly::Actor::GetLocation() const
{
	return mSprite.getPosition();
}

void ly::Actor::SetRotation(float newRotation)
{
	mSprite.setRotation(newRotation);
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

sf::Vector2f ly::Actor::GetRightDirection() const
{
	return Rotation2Vecor(GetRotataion()+90.f);
}

void ly::Actor::CenterPivot()
{
	sf::FloatRect bound = mSprite.getGlobalBounds();
	mSprite.setOrigin(bound.width / 2, bound.height / 2);
}

#include "framework/Actor.h"
#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/sinks/ConsoleSink.h>
#include "framework/Core.h"
#include "framework/AssetManager.h"

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
	AssetManager& assetMgr = AssetManager::GetInstance();
	if (!mTexture.loadFromFile(path)) {
		LOG_ERROR(mlogger, "Cannot load image from path({})", path);
	}
	else {
		mSprite.setTexture(mTexture);
		int tWidth = mTexture.getSize().x;
		int tHeight = mTexture.getSize().y;
		mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{tWidth, tHeight} });
	}
}

void ly::Actor::Render(sf::RenderWindow& win)
{
	if (IsPendingDestory()) {
		return;
	}

	win.draw(mSprite);
}

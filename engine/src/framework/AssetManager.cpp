#include "framework/AssetManager.h"
#include "framework/Core.h"

//ly::unique<ly::AssetManager> ly::AssetManager::mPtrAssetManager{ nullptr };
namespace ly {
	//Because it is static, we nned to initialized it before use.
	unique<AssetManager> ly::AssetManager::mPtrAssetManager{ nullptr };

	AssetManager& AssetManager::GetInstance()
	{
		if (!mPtrAssetManager) {
			mPtrAssetManager = unique< AssetManager>{ new AssetManager };
		}

		return *mPtrAssetManager;
	}

	shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		auto found = mLoadedTextureMap.find(path);//it return iterator 
		if (found != mLoadedTextureMap.end())
		{
			return found->second;
		}

		shared<sf::Texture> newTexture{ new sf::Texture };
		if (newTexture->loadFromFile(path))
		{
			mLoadedTextureMap.insert({ path, newTexture });
			return newTexture;
		}

		return shared<sf::Texture> {nullptr};
	}

	ly::AssetManager::AssetManager()
	{

	}
}

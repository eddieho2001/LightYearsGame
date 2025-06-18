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

	ly::AssetManager::AssetManager()
	{

	}
}

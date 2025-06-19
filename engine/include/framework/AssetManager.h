#pragma once

#include "framework/Core.h"
#include <SFML/Graphics.hpp>

namespace ly {
	/*
		1 - Solve the problem for managing asset resource load and manage memory for the game
		2 - Using singleton pattern because one game should have only one AssetManager
		3 - it respond for load/create/store a sf::Texture object from a map to avoid multiple create/load same resources.  
	*/
	class AssetManager {
	public:
		static AssetManager& GetInstance();
		shared<sf::Texture> LoadTexture(const std::string& path);
		void CleanCycle();
		void SetAssetRootDir(const std::string& p_strDir);
	protected:
		//Note that the constructor here, only inetrnal code can do the initialization, outside the class cannot!
		AssetManager();
		
	private:
		static unique<AssetManager> mPtrAssetManager;
		//Dictionary<std::string&, shared<sf::Texture>> mLoadedTextureMap;
		Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
		std::string mRootDir;
	};
}
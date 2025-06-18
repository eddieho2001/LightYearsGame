#pragma once

#include "framework/Core.h"

namespace ly {
	/*
		1 - Solve the problem for managing asset resource load and manage memory handle for the game
		2 - Using singleton pattern because one game should have only one AssetManager
	*/
	class AssetManager {
	public:
		static AssetManager& GetInstance();
	protected:
		//Note that the constructor here, only inetrnal code can do the initialization, outside the class cannot!
		AssetManager();
		
	private:
		static unique<AssetManager> mPtrAssetManager;
	};
}
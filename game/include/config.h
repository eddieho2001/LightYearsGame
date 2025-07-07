#pragma once
#include<string>
std::string GetResourceDir() {
#ifdef NDEBUG //for release build
	return "assets/";
#else
	return "D:/MyDocs/GameDev/Udemy/LearnC++AndMakeaGameFromScratch/Section06/LightYearsGame/game/assets/";
#endif
}

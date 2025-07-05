#pragma once
#include<string>
std::string GetResourceDir() {
#ifdef NDEBUG //for release build
	return "assets/";
#else
	return "C:/Projects/UdemyCourses/C++/LearnC++AndMakeaGameFromScratch/Section06/LightYearsGame/game/assets/";
#endif
}

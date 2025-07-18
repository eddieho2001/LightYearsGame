#pragma once

#include<stdio.h>
#include<memory>
#include<map>
#include<unordered_map>
#include<unordered_set>

namespace ly {
	//using template alias declarations using keyword for declare alias
	template<typename T>
	using unique = std::unique_ptr<T>;

	template<typename T>
	using shared = std::shared_ptr<T>;

	template<typename T>
	using weak = std::weak_ptr<T>;

	template<typename T>
	using List = std::vector<T>;

	template<typename keyType, typename valType, typename compType = std::less<keyType>>
	using Map = std::map<keyType, valType, compType>;

	template<typename keyType, typename valType, typename hasher = std::hash<keyType>>
	using Dictionary = std::unordered_map<keyType, valType, hasher>;
	
	template<typename T>
	using Set = std::unordered_set<T>;

	//Data type for implement team id so that there are max 255 team
	using uint8 = unsigned char;

	const static uint8 neturalTeamId = 255;

#define _LOG(M, ...) printf(M "\n", ##__VA_ARGS__)

}
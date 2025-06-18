#pragma once

#include<stdio.h>
#include<memory>
#include<map>
#include<unordered_map>
#include<unordered_set>

namespace ly {
	//declared unique as nickname as unique pointer
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

#define _LOG(M, ...) printf(M "\n", ##__VA_ARGS__)

}
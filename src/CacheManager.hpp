#pragma once

#include<string>
#include <unordered_map>
#include <list> 

class CacheManager {
private:
	std::unordered_map<std::string, std::string> cache_map;
	std::list <std::string> cache_list;
	//the biggest size the cache can be
	int capacity;
	//the current size
	int size = 0;

	void removeFromCache();
	void refer(const std::string& path);

public:
	CacheManager(const int capacity);
	void insert(const std::string& path, const std::string& s);
	std::string get(const std::string& path);
};
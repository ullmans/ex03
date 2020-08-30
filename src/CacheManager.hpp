#pragma once

#include <unordered_map>
#include <list> 

class CacheManager {
private:
	std::unordered_map<std::string, std::string> cache_map;
	std::list <std::string> cache_list;
	int capacity;
	int size = 0;

	void removeFromCache(const int capacity);

public:
	CacheManager(const int capacity);
	void insert(const std::string& path, const std::string& s);
	std::string get(const std::string& path);
};
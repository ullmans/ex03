#pragma once

#include <unordered_map>

class CacheManager {
private:
	std::unordered_map<std::string, std::string> cache_map;
	int capacity;
	int size = 0;
public:
	CacheManager(const int capacity);
	void insert(const std::string& path, const std::string& s);
	std::string get(const std::string& path);
};
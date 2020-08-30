#include <iostream>
#include <unordered_map>
#include "CacheManager.hpp"
#include "file_reading.hpp"

CacheManager::CacheManager(const int capacity) {
	this->capacity = capacity;
}

void CacheManager::insert(const std::string& path, const std::string& content) {
	try {
		writeFileContent(path, content);
	}
	catch (std::exception e) {
		//Handle Error
		return;
	}
	cache_map[path] = content;
	size++;
}

std::string CacheManager::get(const std::string& path) {
	if (cache_map.find(path) == cache_map.end()) {
		std::string content;
		try {
			content = readFileContent(path);
		}
		catch (std::exception e) {
			//Handle Error
			return e.what();
		}
		cache_map[path] = content;
	}
	return cache_map[path];
}
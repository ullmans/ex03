#include<string>
#include <unordered_map>
#include <list> 
#include "CacheManager.hpp"
#include "file_reading.hpp"

void CacheManager::removeFromCache() {
	std::string temp = cache_list.back();
	cache_list.pop_back();
	cache_map.erase(temp);
	size--;
}

void CacheManager::refer(const std::string& path) {
	if (cache_map.find(path) != cache_map.end()) {
		for (auto it = cache_list.begin(); it != cache_list.end(); ++it) {
			if (*it == path) {
				cache_list.erase(it);
				size--;
				break;
			}
		}
	}
	cache_list.push_front(path);
	size++;
	if (size > capacity) {
		removeFromCache();
	}
}

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
	refer(path);
	cache_map[path] = content;
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
	refer(path);
	return cache_map[path];
}
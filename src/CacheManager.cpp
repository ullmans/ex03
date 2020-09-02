#include <iostream>

#include "file_reading.hpp"
#include <string>
#include <algorithm>
#include <unordered_map>
#include <list>
#include "MessageException.hpp"
#include "CacheManager.hpp"

const std::string PATH_TO_LRU_LIST = "lru_list.txt";

void CacheManager::removeLRUElementFromCache() {
	std::string lruKey = lru_list.back();
	std::string lruPath = cache_map[lruKey];
	if (remove(lruPath.c_str()) != 0) {
		throw MessageException("File delete failed");
	}
	else {
		lru_list.pop_back();
		cache_map.erase(lruKey);
	}
}

void CacheManager::moveToFrontOfLRUList(const std::string& key) {
	for (auto it = lru_list.begin(); it != lru_list.end(); ++it) {
		if (*it == key) {
			lru_list.erase(it);
			lru_list.push_front(key);
			return;
		}
	}
}

CacheManager::CacheManager(const int capacity) {
	this->capacity = capacity;
	std::string lru_list_string;
	try {
		lru_list_string = readFileContent(PATH_TO_LRU_LIST);
	}
	catch (MessageException me) {
		return;
	}
	std::string keyTemp;
	std::string pathTemp;
	bool isReadingKey = true;
	for (auto it = lru_list_string.begin(); it != lru_list_string.end(); it++) {
		if (*it == '|') {
			isReadingKey = false;
		}
		else if (*it == '\n') {
			lru_list.push_back(keyTemp);
			cache_map[keyTemp] = pathTemp;
			keyTemp.clear();
			pathTemp.clear();
			size++;
			isReadingKey = true;
		}
		else if (isReadingKey) {
			keyTemp += *it;
		}
		else {
			pathTemp += *it;
		}
	}
}

CacheManager::~CacheManager() {
	std::string lru_list_string;
	for (const std::string& s : lru_list) {
		lru_list_string += s + '|' + cache_map[s] + "\n";
	}
	try {
		writeFileContent(PATH_TO_LRU_LIST, lru_list_string);
	}
	catch (std::exception e) {
		return;
	}
}

void CacheManager::insert(const std::string& key, const std::string& path, const std::string& content) {
	if (path == PATH_TO_LRU_LIST) {
		throw MessageException(PATH_TO_LRU_LIST + "can't be added to cache");
	}
	if (std::count(path.begin(), path.end(), '\n') != 0 || std::count(path.begin(), path.end(), '|') != 0) {
		throw MessageException("Characters '\\n' and '|' are not allowed in the keys");
	}
	try {
		writeFileContent(path, content);
	}
	catch (MessageException me) {
		throw me;
	}
	if (search(key)) {
		moveToFrontOfLRUList(key);
	}
	else {
		lru_list.push_front(key);
		if (size == capacity) {
			removeLRUElementFromCache();
		}
		else {
			size++;
		}
	}
	cache_map[key] = path;
}

std::string CacheManager::get(const std::string& key) {
	if (!search(key)) {
		throw MessageException("ERROR: No such key exists in cache");
	}
	std::string content;
	try {
		content = readFileContent(cache_map[key]);
	}
	catch (MessageException me) {
		throw me;
	}
	moveToFrontOfLRUList(key);
	return content;
}

bool CacheManager::search(const std::string& key) const {
	return cache_map.find(key) != cache_map.end();
}

void CacheManager::clear() {
	while (size > 0) {
		removeLRUElementFromCache();
		size--;
	}
}
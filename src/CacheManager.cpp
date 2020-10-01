#include "file_reading.hpp"
#include <string>
#include <algorithm>
#include <unordered_map>
#include <list>
#include "MessageException.hpp"
#include "CacheManager.hpp"

#include <iostream>

void CacheManager::removeLRUFileFromCache() {
	//The lru key is the key in the back of lru_list.
	std::string lruKey = m_lru_list.back();

	std::string lruPath = "./bin/cache/" + m_cache_map[lruKey];

	//Trying to delete the file associated with the key from the cache.
	if (remove(lruPath.c_str()) != 0) {
		throw MessageException("File deletion failed");
	}
	else {
		m_lru_list.pop_back();
		m_cache_map.erase(lruKey);
		size--;
	}
}

void CacheManager::moveToFrontOfLRUList(const std::string& key) {
	//Iterating through lru_list in order to find the key,
	//and if it's there it'll be moved to the front of the lru_list.
	for(auto& c: m_lru_list){
		if (c == key) {
			m_lru_list.remove(c);
			m_lru_list.push_front(key);
			return;
		}
	}
}

CacheManager::CacheManager(const int capacity) : m_capacity(capacity) { }

std::uint32_t CacheManager::getCapacity() const{
	return m_capacity;
}

void CacheManager::loadCacheList() {
	//Holds the content of ./bin/cache_list.txt
	std::string cache_list_content;
	try {
		cache_list_content = readFileContent("./bin/cache/cache_list.txt");
	}
	//if there are no files (a new catch) so return (there are no nedd for a failure).
	catch (MessageException& me) {
		return;
	}

	//Holds one of the keys that are read from cache_list_content
	std::string keyTemp;

	//Holds one the filename associated with the key in keyTemp
	std::string pathTemp;

	//Holds true if the function is currently reading into keyTemp,
	//or false if the function is currently reading into pathTemp
	bool isReadingKey = true;

	//Iterating through cache_list_content to get keys and paths
	for (auto it = cache_list_content.begin(); it != cache_list_content.end(); it++) {
		//The character '|' is the seperator between the keys and the
		//paths in each line of cache_list_content
		if (*it == '|') {
			//The line starts with a key, so now a filename will be read
			isReadingKey = false;
		}
		//The character '\n' is the seperator between the files (the keys and paths) in cache_list_content,
		//so now keyTemp and pathTemp are put in the cache and then they are cleared for the next file
		else if (*it == '\n') {
			//lru_list needs to have the same order as cache_list_content, and cache_list_content starts
			//with the most recently used file, so each time we read a file it is put in the back of lru_list
			m_lru_list.push_back(keyTemp);

			m_cache_map[keyTemp] = pathTemp;
			keyTemp.clear();
			pathTemp.clear();
			++size;

			//Next line starts with a key
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

void CacheManager::saveCacheList() {
	//Holds the content that'll be written into ./bin/cache_list.txt
	std::string cache_list_content;

	//Each key in lru_list is put in cache_list_content in order.
	for (const std::string& s : m_lru_list) {
		//Each line in cache_list_content looks like "<key>|<filename>"
		cache_list_content += s + "|" + m_cache_map[s] + "\n";
	}

	//Writing cache_list_content into ./bin/cache_list.txt
	try {
		writeFileContent("./bin/cache/cache_list.txt",cache_list_content);
	}
	catch (MessageException& me) {
		throw MessageException("Saving cahce_list.txt failed because: " + std::string(me.what()));
	}
}

void CacheManager::insert(const std::string& key, const std::string& filename, const std::string& content) {
	if (std::count(filename.begin(), filename.end(), '\n') != 0 || std::count(filename.begin(), filename.end(), '|') != 0) {
		throw MessageException("Characters '\\n' and '|' are not allowed in the keys");
	}

	//The content is written into the file
	try {
		writeFileContent("./bin/cache/" + filename, content);

	}
	catch (MessageException& me) {
		throw MessageException("Writing the inserted file failed because: " + std::string(me.what()));
	}

	//If the key already exists in the cache, it'll be moved to the front of lru_List. Else, it'll be
	//pushed to front of the lru_list, and if the cache is already full, and lru file will be deleted.
	if (search(key)) {
		moveToFrontOfLRUList(key);
	}
	else {
		m_lru_list.push_front(key);
		if (size == m_capacity) {
			removeLRUFileFromCache();
		}
		size++;
	}

	m_cache_map[key] = filename;
}

std::string CacheManager::get(const std::string& key) {
	if (!search(key)) {
		throw MessageException("ERROR: No such key exists in the cache");
	}
	std::string content;
	try {
		content = readFileContent("./bin/cache/" + m_cache_map[key]);
	}
	catch (MessageException& me) {
		throw MessageException("Reading from the file associated with the key failed because: " + std::string(me.what()));
	}
	moveToFrontOfLRUList(key);
	return content;
}

bool CacheManager::search(const std::string& key) const {
	return m_cache_map.find(key) != m_cache_map.end();
}

void CacheManager::clear() {
	while (size > 0) {
		removeLRUFileFromCache();
	}
}
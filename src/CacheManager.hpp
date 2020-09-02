#ifndef CACHE_MANAGER_H
#define CACHE_MANAGER_H

#include <string>
#include <unordered_map>
#include <list>
#include <cstdint>

class CacheManager {
private:
	std::unordered_map<std::string, std::string> cache_map;
	std::list <std::string> lru_list;
	//the biggest size the cache can be
	std::uint32_t capacity;
	//the current size
	std::uint32_t size = 0;

	void removeLRUElementFromCache();
	void moveToFrontOfLRUList(const std::string& key);
public:
	CacheManager(const int capacity);
	~CacheManager();
	void insert(const std::string& key, const std::string& path, const std::string& content);
	std::string get(const std::string& key);
	bool search(const std::string& key) const;
	void clear();
};

#endif
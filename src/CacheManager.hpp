#ifndef CACHE_MANAGER_H
#define CACHE_MANAGER_H

#include <string>
#include <unordered_map>
#include <list>
#include <cstdint>

class CacheManager {
private:
	//A map that contains all the keys and paths to the file in the cache.
	std::unordered_map<std::string, std::string> m_cache_map;

	//A list that orders the keys by how recently used they are. The most recently
	//used key is in the front while the least recently used is in the back.
	std::list <std::string> m_lru_list;

	//The biggest size the cache can be.
	std::uint32_t m_capacity;

	//The current ammount of files in the cache.
	std::uint32_t size = 0;

	/*
	 * @brief Deletes the lru file from the cache.
	 *
	 * @throws MessageException if the deletion of the file failed.
	 */
	void removeLRUFileFromCache();

	/*
	 * @brief If the key is already in the cache, it is moved to the front of lru_list.
	 *
	 * @param key The key that has just been used.
	 */
	void moveToFrontOfLRUList(const std::string& key);
public:
	/*
	 * @brief Constructor.
	 *
	 * @param key The capacity of the cache. The cache can't hold more files than the capacity.
	 */
	explicit CacheManager(const int capacity);

	/*
	 * @brief Gets the capacity of the cache.
	 *
	 * @return The capacity of the cache.
	 */
	std::uint32_t getCapacity() const;

	/*
	 * @brief Reads from ./bin/cache_list.txt in order to get the keys from the previous
	 * time we used the cache, their order and their paths, and saves them on the cache.
	 *
	 * @throws MessageException if reading from ./bin/cache_list.txt failed.
	 */
	void loadCacheList();

	/*
	 * @brief Saves all the keys and their paths with the order of lru_list in the file "./bin/cache_list.txt".
	 * This file will be used in the next time we run the program because it contatins the current state of the cache.
	 *
	 * @throws MessageException if saving ./bin/cache_list.txt failed.
	 */
	void saveCacheList();

	/*
	 * @brief Inserts a new file into the cache. Removes the lru file if the cache is already full.
	 *
	 * @param key The key of the inserted file.
	 * @param filename The filename of the inserted file.
	 * @param content The content of the inserted file.
	 * @throws MessageException If the key contains characters '\\n' and '|' as they are not allowed.
	 * @throws MessageException If writing to inserted file failed.
	 */
	void insert(const std::string& key, const std::string& filename, const std::string& content);

	/*
	 * @brief Gets the content of the file associated with the key.
	 *
	 * @param key The key of the file.
	 * @throws MessageException If no such key exists in the cache.
	 * @throws MessageException If Reading from the file associated with the key failed.
	 * @return The content of the file in the file filename associated with the key.
	 */
	std::string get(const std::string& key);

	/*
	 * @brief Checks if the key is in the cache.
	 *
	 * @param key The checked key.
	 * @return true if the key exists and false otherwise.
	 */
	bool search(const std::string& key) const;

	/*
	 * @brief Deletes all files assocaited with the cache other than ./bin/cache_list.txt.
	 *
	 * @throws MessageException if the deletion of one of the files failed.
	 */
	void clear();
};

#endif
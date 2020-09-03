# CacheManager
The cache has a map that stores keys and filenames. The elements of the cache are accessible with their keys. Each key has an
associated file that is stored in ./bin/cache under the filename of the key. The key writes into and reads from these files
when they are accessed with their keys.
The cache works as an LRU cache. The cache has a list that stores all the keys in their order. The front of the list
is the most recently used file, and the back is the list recently used file.
The cache is initialized with a certain capacity. When a new file is inserted and the cache is already full, the LRU file is
deleted from the cache.
The cache has a file called ./bin/cache_list.txt . When the cache saves into this file, it saves each key and filename in the
order of the LRU list. Each line in cache_list looks like <key>|<filename>, when the first line comes from the front of the
LRU list and the last line comes from the back of the LRU list. This way, the next time the program is runned, the cache can
load cache_list and get back all its data from the previous run.
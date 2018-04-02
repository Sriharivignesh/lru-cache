#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <list>

class LRUCache {
private:
    int capacity;
    std::list<std::pair<int, int>> lru_list;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> key_map;

public:
    LRUCache(int _capacity): capacity(_capacity) {}
    
    int get(int key) {
        if(key_map.count(key) == 0)
        {
            return -1;
        }

        // Element is there in the cache
        // Move it to the front of the list and return
        std::list<std::pair<int, int>>::iterator list_it = key_map[key];
        int value = key_map[key]->second;
        lru_list.erase(key_map[key]);
        lru_list.push_front(std::make_pair(key, value));
        key_map[key] = lru_list.begin();
      
        return key_map[key]->second;
        
    }
    
    void put(int key, int value) {
        // Check if the key is in the map
        // If so update the list after checking
        // if the list is full or not
        if(key_map.count(key) == 0)
        {
            if(lru_list.size() == capacity)
            {
                // Cache is full, need to purge
                key_map.erase(lru_list.back().first);
                lru_list.pop_back();
            }

            // Insert the key, value in the front of the list
            // Add value to the map
            lru_list.push_front(std::make_pair(key, value));
            key_map[key] = lru_list.begin();
        }
        else
        {
            // Key already exists in the cache
            // std::list<int, int>::iterator list_it = key_map[key];
            lru_list.erase(key_map[key]);
            lru_list.push_front(std::make_pair(key, value));
            key_map[key] = lru_list.begin();
        }
   }
};

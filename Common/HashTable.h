//
//  HashTable.h
//  SocialNetwork
//
//  Created by admin on 16/03/2019.
//  Copyright © 2019 admin. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

#include <unordered_map>

template <class K, class V>
class HashTable {
    
    typedef std::unordered_multimap<K, const V * > Lookup;
    Lookup m_lookup;
    
public:
    void addObject(const K & key, const V & value) {
        V * v = new V(value);
        m_lookup.emplace(key, v);
    }
    
    const V * deleteObject(const V & object) {
        auto lambda = [&object](const typename HashTable<K,V>::Lookup::value_type & v) -> bool { return *v.second == object; };
        auto c_it = std::find_if(m_lookup.begin(), m_lookup.end(), lambda);
        
        m_lookup.erase(c_it);
        return c_it->second;
    }
    
    std::vector<const V *> searchObjects( const K & pred) {
        std::vector<const V *> objects = {};
        
        auto robjects = m_lookup.equal_range(pred);
        auto lambda = [&objects](const typename HashTable<K,V>::Lookup::value_type & v){objects.emplace_back(v.second);};
        
        for_each (robjects.first, robjects.second, lambda);
        return objects;
    }
};


#endif /* HashTable_h */

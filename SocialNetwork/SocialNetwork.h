//
//  SocialNetwork.hpp
//  SocialNetwork
//
//  Created by admin on 16/03/2019.
//  Copyright © 2019 admin. All rights reserved.
//

#ifndef SocialNetwork_hpp
#define SocialNetwork_hpp

#include <stdio.h>
#include <string>
#include "HashTable.h"
#include <vector>

template <typename K>
class User {

    static std::atomic<K> count;
    
public:
    User (const std::string & name, uint8_t age=0, std::vector<std::string> hobbies = {} ) :
    m_id(++count), m_name(name) , m_age(age), m_hobbies(hobbies)
    {}
    
    User (const User & user) :
    m_name(user.m_name), m_age(user.m_age), m_id(user.m_id), m_hobbies(user.m_hobbies)
    {}
    
    bool operator==(const User<K> & u) const
    {
        return u.m_id == m_id;
    }
    
    bool operator==(const User<K> * u) const
    {
        return u->m_id == m_id;
    }
    
    const K & getId() const {return m_id;}
    uint8_t getAge () const {return m_age;}
    std::string getName () const {return m_name;}
    std::vector<std::string> getHobbies() const {return m_hobbies;}
    std::vector<K> getFriends() const {return m_friends;}
    
private:
    const K m_id;
    const std::string & m_name;
    uint8_t m_age;
    const std::vector<std::string> m_hobbies;
    const std::vector<K> m_friends;
};

template <typename K>
class SocialNetwork {
   
public:
    
    void addUser (const User<K> & user) {
        m_nameLookup.addObject(user.getName(), user);
        m_ageLookup.addObject(user.getAge(), user);
        m_idLookup.addObject(user.getId(), user);
        
        for (const auto & hit : user.getHobbies() ) {
            m_hobbiesLookup.addObject(hit, user);
        }
    }
    
    void deleteUser(const User<K> & user) {
        delete (m_nameLookup.deleteObject(user));
        delete (m_ageLookup.deleteObject(user));
        delete (m_idLookup.deleteObject(user));
        delete(m_hobbiesLookup.deleteObject(user));
    }
    
    std::vector<const User<K> *> searchUserByName(const std::string & name){
        return m_nameLookup.searchObjects(name);
    }
    
    std::vector<const User<K> *>searchUserByAge(const uint8_t age) {
        return m_ageLookup.searchObjects(age);;
    }
    
    std::vector<const User<K> *> searchUserByHobbies(const std::vector<std::string> & hobbies) {
        const auto & hobby = hobbies.begin();
        auto objects = m_hobbiesLookup.searchObjects(*hobby);
        
        auto removeUser = [&hobbies](auto user)-> bool
                                            {
                                                for (const auto & hobby : hobbies)
                                                {
                                                    auto lhobbies = user->getHobbies();
                                                    auto result = std::find(lhobbies.begin(), lhobbies.end(), hobby );
                                                    if (result == lhobbies.end()) return true;
                                                }
                                                return false;
                                            };
        
        auto it = std::remove_if(objects.begin(), objects.end(), removeUser);
        objects.erase( it, objects.end() );
        return objects;
    }
    
    std::vector<K> getFriendsOfUser(const User<K> & user) {
        
        auto  luser = m_friendsLookup.find(user.getId());
        
        if (luser == m_friendsLookup.end()) {
            return {};
        }
        
        return luser->second;
    }
    
private:
    
    HashTable<std::string, User<K> > m_nameLookup;
    HashTable<int,  User<K> > m_ageLookup;
    HashTable<std::string, User<K> > m_hobbiesLookup;
    
    HashTable<K, User<K>> m_idLookup;
    std::unordered_map<K, std::vector<K> > m_friendsLookup;
};


template<typename K>
std::atomic<K> User<K>::count{0};


#endif /* SocialNetwork_hpp */

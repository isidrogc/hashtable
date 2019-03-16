//
//  main.cpp
//  SocialNetwork
//
//  Created by admin on 16/03/2019.
//  Copyright © 2019 admin. All rights reserved.
//

#include <iostream>
#include "SocialNetwork.h"


int main(int argc, const char * argv[]) {
   
    SocialNetwork<unsigned int> socialNetwork;
    
    User<unsigned int> Mia ("Mia", 50, {"books", "swimming", "movies"});
    User<unsigned int> Pia ("Pia", 50, {"books", "jogging"});
    User<unsigned int> Pia2 ("Pia", 100, {"books", "reading"});
    User<unsigned int> Mia2 ("Mia", 50, {"books", "swimming"});
    
    std::vector<const User<unsigned int> * > test {};
    
    test = socialNetwork.searchUserByName("Mia");
    assert (test.size() == 0);
    
    // Action add
    socialNetwork.addUser(Mia);
    socialNetwork.addUser(Pia);
    socialNetwork.addUser(Mia2);
    socialNetwork.addUser(Pia2);
   
    // test search after add
    test = socialNetwork.searchUserByName("Mia");
    assert (test.size() == 2);
    
    test = socialNetwork.searchUserByAge(50);
    assert (test.size() == 3);
    
    test = socialNetwork.searchUserByHobbies({"books"});
    assert (test.size() == 4);
    
    test = socialNetwork.searchUserByHobbies({"books", "swimming"});
    assert (test.size() == 2);
    
    test = socialNetwork.searchUserByHobbies({"movies"});
    assert (test.size() == 1);
    
    // test friends
    auto friends = socialNetwork.getFriendsOfUser(Mia);
    assert (friends.size() == 0);
    
    // action delete
    socialNetwork.deleteUser(Mia2);
    
    // test search after delete
    test = socialNetwork.searchUserByName("Mia");
    assert (test.size() == 1);
    
    test = socialNetwork.searchUserByAge(50);
    assert (test.size() == 2);
    
    test = socialNetwork.searchUserByHobbies({"books"});
    assert (test.size() == 3);
    
    test = socialNetwork.searchUserByHobbies({"books", "swimming"});
    assert (test.size() == 1);
    
    
}

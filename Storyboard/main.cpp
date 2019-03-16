//
//  main.cpp
//  work
//
//  Created by admin on 14/03/2019.
//  Copyright © 2019 admin. All rights reserved.
//

#include <iostream>
#include "Storyboard.hpp"

int main(int argc, const char * argv[]) {
    
    Storyboard storyBoard;
    
    Note n1 ("send BT signal", "When agent enter the system", {"BT", "signal", "android", "iOS"} );
    Note n2 ("send BT signal", "When agent leave the system", {"BT", "signal", "android", "iOS"} );
    Note n3 ("process AI signal", "When system react to agent", {"AI", "signal", "android", "iOS"} );
    Note n4 ("process AI signal", "When agent react system", {"relC.8", "android", "iOS"} );
    Note n5 ("the smoke", "Is here but not there", {"smoke"});
    
    storyBoard.addNote(n1);
    storyBoard.addNote(n2);
    storyBoard.addNote(n3);
    storyBoard.addNote(n4);
    
    std::vector<const Note *> test = {};
    
    test = storyBoard.searchByTitle("the smoke");
    assert(test.size() == 0);
    
    test = storyBoard.searchByTitle("send BT signal");
    assert(test.size() == 2);
    assert(test[0]->getTitle() == "send BT signal");
    assert(test[1]->getTitle() == "send BT signal");
    
    test = storyBoard.searchByText("When system react to agent");
    assert(test.size() == 1);
    assert(test[0]->getTitle() == "process AI signal");
    
    storyBoard.deleteNote(n1);
    test = storyBoard.searchByTitle("send BT signal");
    assert(test.size() == 1);
    assert(test[0]->getText() == "When agent leave the system");
    
    test = storyBoard.searchByTags({"BT", "signal"});
    assert(test.size() == 2);
    
    storyBoard.deleteNote(n5);
    
    return 0;
}

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "doctest.h"
using namespace std;


#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
using namespace ariel;



TEST_CASE("check init values for Player"){

    Player p1("name1");
    Player p2("name2");

    CHECK(p2.getName() == "name2");
    CHECK(p1.getName() == "name1");

    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
    
    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);
    
}

TEST_CASE("check init values for Game"){

    Player p1("name1");
    Player p2("name2");

    Game game(p1,p2);

    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);

    //sould be able to play the first turn and the entire game
    CHECK_NOTHROW(game.playTurn());
    CHECK_NOTHROW(game.playAll());
    //sould not throw an exeption, just returns the right message
    CHECK_NOTHROW(game.printLog());
    CHECK_NOTHROW(game.printWiner());
    CHECK_NOTHROW(game.printStats());
    CHECK_NOTHROW(game.printLastTurn());

    
}

TEST_CASE("check playTurn() ones"){

    Player p1("name1");
    Player p2("name2");

    Game game(p1,p2);
    
    game.playTurn();

    int result = p1.cardesTaken() + p2.cardesTaken();
    int result2 = p1.stacksize() + p2.stacksize();
    CHECK(result >= 1);
    //no cards lost
    CHECK(result2 <= 50);
    
}



TEST_CASE("check seters and geters for player"){

    Player p1("name1");
    p1.setName("new_name");

    //compare() returns 0 if the strings are the same
    CHECK(p1.getName().compare("new_name") == 0);
    CHECK_NOTHROW(p1.setName("new_name"));
    //empty name is not exeptable
    CHECK_THROWS(p1.setName(""));
}




TEST_CASE("check after the game ends"){
    Player p1("name1");
    Player p2("name2");

    Game game(p1,p2);
    game.playAll();
    
    int result = p1.stacksize() + p2.stacksize();
    int result2 = p1.cardesTaken() + p2.cardesTaken();
    CHECK(result == 0);

     

    CHECK(result2 == 52);

    //cant play
    CHECK_THROWS(game.playAll()); 
    CHECK_THROWS(game.playTurn());
}
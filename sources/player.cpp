#include "player.hpp"
using namespace ariel;
using namespace std;

Player::Player(){
    this->name = "name";
    this->cardsTaken = 0;
    this->stackSize = 0;
}

void Player::pushHand(card c){
    this->hand.push_back(c);
}

card Player::pullHand(){
    card c = this->hand.back();
    this->hand.pop_back();
    this->stackSize--;
    return c;
}

void Player::pushWon(card c){
    this->woncards.push_back(c);
}

card Player::pullWon(){
    card c = this->woncards.back();
    this->woncards.pop_back();
    return c;
}

Player::Player(string name){
    this->name = name;
    this->cardsTaken = 0;
    this->stackSize = 0;
}

int Player::stacksize() {
    
    return this->stackSize;
}

void Player::setName(string newName){
    this->name = newName;
    
}
        
string Player::getName(){
    return this->name;
}

string Player::printSuit(const suit& s) {
    switch (s) {
        case club:
            return "club";
        case diamonds:
            return "diamonds";
        case heart:
            return "heart";
        case spades:
            return "spades";
        default:
            return "Unknown suit";
    }
}

string Player::printValue(const value& v) {
    switch (v) {
        case king:
            return "king";
        case queen:
            return "queen";
        case jack:
            return "jack";
        case ace:
           return "ace";
        case tow:
            return "tow";
        case tree:
           return "tree";
        case four:
            return "four";
        case five:
            return "five";
        case six:
            return "six";
        case seven:
            return "seven";
        case eight:
            return "eight";
        case nine:
            return "nine";
        case ten:
            return "ten";
        default:
            return "Unknown value";
    }
}

void Player::printHand(){
    for(auto& c : this->hand){
        cout << "Suit: " << printSuit(c.getSuit()) << ", value: " << printValue(c.getValue()) << endl;
    }
}
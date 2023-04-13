#include "card.hpp"
using namespace ariel;
using namespace std;

card::card(suit s, value v){
    this->shape = s;
    this->val = v;
}

card::card(){

}

void card::setSuit(suit s){
    this->shape = s;
}

void card::setValue(value v){
    this->val = v;
}

suit card::getSuit(){
    return this->shape;
}

value card::getValue(){
    return this->val;
}

string card::printSuit(const suit& s) {
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

string card::printValue(const value& v) {
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


std::string card::tostring(){
    return "suit: " + printSuit(this->shape) + " value: " + printValue(this->val);
}


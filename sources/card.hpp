#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <string>

namespace ariel{

    enum suit{club, diamonds, heart, spades};
    enum value{king=13, queen=12, jack=11, ace=1, tow=2, tree=3, four=4, five=5, six=6, seven=7, eight=8, nine=9, ten=10};

    class card{
        public:
            card(suit, value);
            card();
            suit getSuit();
            value getValue();
            bool isBigger(value l, value r);
            void setSuit(suit s);
            void setValue(value v);
            std::string tostring();
            std::string printValue(const value& v);
            std::string printSuit(const suit& s);
            
        private:
            suit shape;
            value val;


    };





}
#endif
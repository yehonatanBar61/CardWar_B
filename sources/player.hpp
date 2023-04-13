#ifndef Player_HPP
#define Player_HPP
#include "card.hpp"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace ariel{

    class Player{

        private:
            string name;
            int stackSize;
            int cardsTaken;
            int win_counter = 0;
            vector<card> hand; // the cards that the player still have
            vector<card> woncards;// the cards that the player has won
            int turn_counter = 1;//amount of turns in the game

        public:
            Player(string name); 
            Player();
            int stacksize();//returns the stack size representing the hand of the player
            void printHand();
            int cardesTaken () const {
                return this->cardsTaken;
            }
            void setcardsTaken(int num){
                this->cardsTaken = num;
            }
            void setStackSize(int size){
                this->stackSize = size;
            }
            string printSuit(const suit& s);
            string printValue(const value& v);
            void pushHand(card d);
            card pullHand();
            void pushWon(card c);
            card pullWon();
            void setName(string);
            string getName();
            void increas_win_counter_byOne(){
                this->win_counter++;
            }
            int getWin_counter() const {
                return this->win_counter;
            }
            int getTurncounter() const {
                return this->turn_counter;
            }
            void increas_turn_counter(){//increases turn counter by one
                this->turn_counter++;
            }


    };
}

#endif
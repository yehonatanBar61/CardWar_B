#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "card.hpp"
#include <iostream>
#include <string>

namespace ariel{
    const int NUM_CARDS = 52;

    class Game{
        private:
            Player* player1;
            Player* player2;
            bool gameover = false;
            std::string lasTurn;
            int draws_count = 0;
            vector<card> playground1;
            vector<card> playground2;
            bool draw = false;//indicates if we are in a draw strike
            vector<std::string> log_trucker;
  
        public:
            Game(Player& player1, Player& player2);
            void playTurn();
            void printLastTurn(); 
            void printWiner();
            void printLog();
            void playAll();
            void printStats();
            void winner(Player& winner, vector<card>& him, vector<card>& his);
            void gameOver();
            void change_last_turn(Player winner, Player loser, card winC, card losC);
            

    };

}

#endif
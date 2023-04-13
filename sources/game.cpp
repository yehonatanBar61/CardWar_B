#include "game.hpp"
#include "player.hpp"
#include "card.hpp"
using namespace std;
using namespace ariel;

namespace ariel{

    void shuffleDeck(card Deck[]){
        srand(time(NULL)); // seed the random number generator with the current time
        int random;
        for (int i = 0; i < 51; i++) {
            random = rand() % 52;
            swap(Deck[i], Deck[random]);
        }
    }

    void dealingCards(card Deck[], Player &p1, Player &p2){
        shuffleDeck(Deck);
        for(int i = 0; i < 26; i++){
            p1.pushHand(Deck[i]);
            p2.pushHand(Deck[i+26]);
        }
    }

    void swap(card &a, card &b){
        card temp = a;
        a = b;
        b = temp;
    }

    Game::Game(Player& p1, Player& p2){
        this->player1 = &p1;
        this->player2 = &p2;

        // if(p1.getName() == p2.getName()){
        //     throw invalid_argument("cant play the game alone");
        // }

        suit types[] = {club, diamonds, heart, spades};
        value value[] = {king, queen, jack, ace, tow, tree, four, five, six, seven, eight, nine, ten};
        int counter = 0;

        card Cards[NUM_CARDS];

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 13; j++){
                card c;
                c.setSuit(types[i]);
                c.setValue(value[j]);
                Cards[counter] = c;
                counter++;
            }
        }
        
        dealingCards(Cards, *this->player1, *this->player2);

        this->player1->setStackSize(26);
        this->player2->setStackSize(26);

        player1->printHand();
        cout << "player 2:------------------" << endl;
        player2->printHand();

    }

    void Game::winner(Player& winner, vector<card>& him, vector<card>& his){
        //if the last turn was draw it ended
        draw = false;
        winner.increas_win_counter_byOne();
        int numOfcards = him.size() + his.size();
        while(!him.empty()){
            card c = him.back();
            him.pop_back();
            winner.pushWon(c);
        }
        while(!his.empty()){
            card c = his.back();
            his.pop_back();
            winner.pushWon(c);
        }
        int temp = winner.cardesTaken();
        winner.setcardsTaken(numOfcards + temp);
        this->log_trucker.push_back(this->lasTurn);
    }

    void Game::playTurn(){

        if(this->player1->getName() == this->player2->getName()){
            throw invalid_argument("cant play the game alone");
        }

        //in order to keep truck (its steel the same turn)
        if(!this->draw){
            this->lasTurn = "";
        }

        if((this->player1->stacksize() <= 0 || this->player2->stacksize() <= 0)){
            if((playground1.size() != 0 || playground2.size() != 0)){
                vector<card> temp;
                winner(*this->player1, this->playground1, temp);
                winner(*this->player2, this->playground2, temp);
                this->playground1.clear();
                this->playground2.clear();
                this->gameOver();
                return;
            }else if((this->player1->cardesTaken() + this->player2->cardesTaken() == 52) && !gameover){
                this->gameOver();
                return; 
            }else{
                this->printLog();
                throw invalid_argument("Can't play you have empty stack of cards");
            }
        }
       
        card top1 = this->player1->pullHand();
        card top2 = this->player2->pullHand(); 

        this->player1->increas_turn_counter();
        this->player2->increas_turn_counter();

        playground1.push_back(top1);
        playground2.push_back(top2);


        //draw
        if(top1.getValue() == top2.getValue()){
            draw = true;
            this->draws_count++;
            this->lasTurn += this->player1->getName() + " got " + top1.tostring() + " " + this->player2->getName()
             + " got " + top2.tostring() + ". draw. ";
            if(this->player1->stacksize() >= 1 && this->player1->stacksize() >= 1){
                card top11 = this->player1->pullHand();
                card top22 = this->player2->pullHand();
                playground1.push_back(top11);
                playground2.push_back(top22);
            }
            playTurn();
        }else{//not draw
            if(top1.getValue() == 1 && top2.getValue() != 2){
                change_last_turn(*this->player1, *this->player2, top1, top2);
                winner(*this->player1, playground1, playground2);
            }else if(top1.getValue() == 2 && top2.getValue() == 1){
                change_last_turn(*this->player1, *this->player2, top1, top2);
                winner(*this->player1, playground1, playground2);
            }else if(top1.getValue() == 1 && top2.getValue() == 2){
                change_last_turn(*this->player2, *this->player1, top2, top1);
                winner(*this->player2, playground2, playground1);
            }else if(top2.getValue() == 1 && top2.getValue() != 2){
                change_last_turn(*this->player2, *this->player1, top2, top1);
                winner(*this->player2, playground2, playground1);
            }else if(top1.getValue() > top2.getValue()){
                change_last_turn(*this->player1, *this->player2, top1, top2);
                winner(*this->player1, playground1, playground2);
            }else{
                change_last_turn(*this->player2, *this->player1, top2, top1);
                winner(*this->player2, playground2, playground1);
            }
            
        }


    }

    void Game::change_last_turn(Player winner, Player loser, card winC, card losC){
         this->lasTurn.append(winner.getName() + " got "
          + winC.tostring() + " " + loser.getName() + " got " + losC.tostring()
          + ". " + winner.getName() + " wins");
    }

    void Game::gameOver(){
        this->gameover = true;
        if(this->player1->cardesTaken() == this->player2->cardesTaken()){
            this->lasTurn.append("Game ended with a draw");
            //cout << "Draw!!! evreybody wins :)" << endl;
        }else if(this->player1->cardesTaken() > this->player2->cardesTaken()){
            this->lasTurn.append(this->player1->getName() + " wins the game");
            //cout << "player1 wins the game!!" << endl;
        }else{
            this->lasTurn.append(this->player2->getName() + " wins the game");
            //cout << "player2 wins the game!!" << endl;
        }

        this->log_trucker.push_back(this->lasTurn);
    }
    

    void Game::playAll(){
        while (this->player1->stacksize() > 0 && this->player1->stacksize() > 0)
        {
            this->playTurn();
        }
        this->playTurn();
    }

    void Game::printLastTurn(){
       cout << this->lasTurn << endl;
    }

    

    void Game::printLog(){
        for(auto c : this->log_trucker){
            cout << c << endl;
        }
    }

    void Game::printStats(){
        double winRateP1 = static_cast<double>(this->player1->getWin_counter()) / ((double)this->player2->getWin_counter() + this->player1->getWin_counter()) * 100;
        double winRateP2 = static_cast<double>(this->player2->getWin_counter()) / ((double)this->player2->getWin_counter() + this->player1->getWin_counter()) * 100;
        double drawRateP1 = static_cast<double>(this->draws_count) / (double) (this->player1->getTurncounter()) * 100;
        double drawRateP2 = static_cast<double>(this->draws_count) / (double) (this->player2->getTurncounter()) * 100;
        cout << this->player1->getName() << ": \n";
        cout << "Win rate = " << winRateP1 << "%\n";
        cout << "Cards won = " << this->player1->getWin_counter() << "\n";
        cout << "Draw rate = " << drawRateP1 << "%\n";
        cout << "Draws = " << this->draws_count << "\n";

        cout << this->player2->getName() << ": \n";
        cout << "Win rate = " << winRateP2 << "%\n";
        cout << "Cards won = " << this->player2->getWin_counter() << "\n";
        cout << "Draw rate = " << drawRateP2 << "%\n";
        cout << "Draws = " << this->draws_count << "\n";
    }

    void Game::printWiner(){
        this->gameover = true;
        if(this->player1->cardesTaken() == this->player2->cardesTaken()){
            cout << "Draw!!! evreybody wins :)" << endl;
        }else if(this->player1->cardesTaken() > this->player2->cardesTaken()){
            cout << "player1 wins the game!!" << endl;
        }else{
            cout << "player2 wins the game!!" << endl;
        }
    }

}

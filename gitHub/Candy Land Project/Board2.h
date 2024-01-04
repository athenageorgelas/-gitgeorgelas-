// CSCI1300 Fall 2023 Project 2
// Author: Athena Georgelas
// Recitation: 102 - Athena Georgelas
//Date: Dec 5, 2023

#ifndef BOARD2_H
#define BOARD2_H

#include <iostream>
#include "Player2.h"
#include "Candy2.h"

using namespace std;

#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"



double isValidChoice(string output, int l, int h);



struct Tile{

    string color;
    string tile_type = "regular tile";
    bool treasure = false;
    bool store = false;
    bool baracade = false;

};

struct Riddle{

    string riddle;

    string answer;

};


class Board{

    private:

        const static int _BOARD_SIZE = 83;


        const static int _MAX_CANDY_STORE = 3;
        const static int _MAX_HIDDEN_TREASURE = 3;

        vector<Character> characters;
        const string COLORS[3] = {MAGENTA, GREEN, BLUE};

        int _candy_store_count;
        int _shortcut_count;
        int _hidden_treasure_count;

        int current_turn;


    public:
        Tile _tiles[_BOARD_SIZE];
        Store stores[3];
        vector<Riddle> riddles;
        GamePlayer players[2];
        Board();

        void resetBoard();
        void displayTile(int);
        void displayBoard();
        int getBoardSize() const;
        int getCandyStoreCount() const;
        bool addCandyStore(int);
        int getCandyStoreIndex(int);
        bool playRockPaperScissors();
        void readRiddles(string);
        void readCharacter(string);
        Character findCharacter(string);
        bool RiddleFunction();
        void hiddenTreasureFunction();
        void calamity();
        void printCharacters();
        void eraseCharacter(string);
        bool validCharName(string);
        Character findChar(string);
        void initPlayer(int, string, Character, vector<Candy>);
        void printMenu();
        void drawCard();
        bool specialTiles();
        void useCandy();
        int finishedGame();
        void play();
        void finalScreen(GamePlayer);
        void winnerToFile(GamePlayer);
        void marshmallowHailstorm();

        vector<Candy> readCandy(string);

        

};

#endif
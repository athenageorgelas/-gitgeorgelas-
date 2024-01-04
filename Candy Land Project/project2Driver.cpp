// CSCI1300 Fall 2023 Project 2
// Author: Athena Georgelas
// Recitation: 102 - Athena Georgelas
//Date: Dec 5, 2023


#include "Board2.h"
#include "Candy2.h"
#include "Player2.h"
#include <iostream>
#include <vector>

using namespace std;

vector<Candy> readCandy(string file_name){

    ifstream file(file_name);

    if (!file.is_open()){
        cout << "Failed to open file"<< endl;
        return {};
    }
    vector<Candy> candies;
    string line;
    getline(file, line);
    while(getline(file, line)){
        stringstream ss(line);
        string  name_func, effect_type_func, description_func, effect_value_func, candy_type_func, price_str_func;

        // Name|Description|Effect type|Effect value|Candy type|Price

        getline(ss, name_func, '|');
        getline(ss, description_func, '|');
        getline(ss, effect_type_func, '|');
        getline(ss, effect_value_func, '|');
        getline(ss, candy_type_func, '|');
        getline(ss, price_str_func, '|');
        Candy cnew;

        //create a new candy struct for function
        cnew.name = name_func;
        cnew.description = description_func;
        cnew.effect_type = effect_type_func;
        cnew.effect_value = stod(effect_value_func);
        cnew.candy_type = candy_type_func;
        cnew.price = stod(price_str_func);

        candies.push_back(cnew);

    } 
    file.close();
    return candies;

}

string isValidString(string output, vector<string> choices) {
    
    cout << output << endl;

    string input;

    while(true){
        getline(cin, input);
        for (int i  = 0; i < choices.size(); i++){
            if(choices[i]==input){
                return input;
            }
       }
        cout << "Invalid input"<< endl;
    }   
}

double isValidChoice(string output, int l, int h) {

    cout << output;

    string input;
    getline(cin, input);

        while(!isdigit(input[0]) || stoi(input) < l || stoi(input) > h){
            cout << "Invalid input."<<endl;
            getline(cin, input);
        }
    
    return stoi(input);
}

int main(){
    srand(time(0));

    Board board;

    vector<Candy> candies = readCandy("candies.txt");
    board.readCharacter("characters.txt");
    board.readRiddles("riddles.txt");
    Store store("Jack and Jill", -1);
    store.candies = {};
    store.readCandy("candies.txt");
    store.addCandyToStore(candies);


    string name1, name2;


    int num_players = isValidChoice("Welcome to the game of candyland. Please enter the number of participants (choose 2):\n", 2, 2);
    cout << "There are " << num_players << " players" << endl;

    cout << "Enter player 1 name" << endl;

    getline(cin, name1);

    cout << "Welcome to candyland "<< name1 <<"! We wish you the best of luck."<<endl<<"Here is a list of characters, please select one."<<endl;

    string char_choice1;

    board.printCharacters();

    getline(cin, char_choice1);

    while(!board.validCharName(char_choice1)){
        cout << "PLease enter a valid input." << endl;
        getline(cin, char_choice1);
    }

    board.initPlayer(0, name1, board.findChar(char_choice1), candies);
    board.eraseCharacter(char_choice1);

    cout << "You have chosen "<< char_choice1 <<endl;
    
    string input = isValidString("Would you like to visit the candy store? (y/n)", {"yes", "no", "y", "n"});

    if(input[0] == 'y'){
        board.players[0] = store.sell(board.players[0]);
    }



    cout << "Enter player 2 name" << endl;

    getline(cin, name2);

    cout << "Welcome to candyland "<< name2 <<"! We wish you the best of luck."<<endl<<"Here is a list of characters, please select one."<<endl;

    string char_choice2;

    board.printCharacters();

    getline(cin, char_choice2);

    while(!board.validCharName(char_choice2)){
        cout << "Please enter a valid input." << endl;
        getline(cin, char_choice2);
    }

    board.initPlayer(1, name2, board.findChar(char_choice2), candies);
    board.eraseCharacter(char_choice2);


    cout << "You have chosen "<< char_choice2 <<endl;
    
    input = isValidString("Would you like to visit the candy store? (y/n)", {"yes", "no", "y", "n"});

    if(input[0] == 'y'){
        board.players[1] = store.sell(board.players[1]);
    }



    cout << "Let's play candyland!"<<endl;


    while(board.finishedGame() == 5){
        board.play();
        
    }

    board.finalScreen(board.players[board.finishedGame()-3]);

    return 0;
}
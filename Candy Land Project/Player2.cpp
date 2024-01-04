// CSCI1300 Fall 2023 Project 2
// Author: Athena Georgelas
// Recitation: 102 - Athena Georgelas
//Date: Dec 5, 2023

#include "Player2.h"



GamePlayer::GamePlayer() {
    _prev_pos = 0;
    _stamina = 0;
    _candy_amount = 0;
    _gold = 0.0;
    _effect = "";
    _player_position = 0;
    immunity = 0;

    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++){
        _inventory[i] = {"", "", "", 0.0, "", 0.0};
    }
}

GamePlayer::GamePlayer(Character choice, int stamina, double gold, string effect, Candy candy_array[], const int CANDY_ARR_SIZE){
    _choice = choice;
    _stamina = stamina;
    _gold = gold;
    _candy_amount = 0;
    _effect = effect;
    _player_position = 0;
    _prev_pos = 0;
    immunity = 0;

    while (_candy_amount < CANDY_ARR_SIZE) {

        _inventory[_candy_amount].name = candy_array[_candy_amount].name;
        _inventory[_candy_amount].description = candy_array[_candy_amount].description;
        _inventory[_candy_amount].price = candy_array[_candy_amount].price;
        _inventory[_candy_amount].candy_type = candy_array[_candy_amount].candy_type;

        bool emptyName = _inventory[_candy_amount].name != "";
        bool emptyDescription = _inventory[_candy_amount].description != "";
        bool emptyPrice = _inventory[_candy_amount].price != 0.0;
        bool emptyCandyType = _inventory[_candy_amount].candy_type != "";

        if ( emptyName && emptyDescription && emptyPrice &&  emptyCandyType){
            _candy_amount++;
        }
    }
}

int GamePlayer::getCandyAmount(){

    return _candy_amount;
}



void GamePlayer::setStamina(int staminaInput){
    if(immunity != 0) {
        cout << player_name << " has an immunity of " << immunity << endl; 
        staminaInput += immunity;
        immunity = 0;
    }

    if(staminaInput <= 0){
        _stamina = 0;
        lose_turn = true;
    }
    else if(staminaInput > 100){
        _stamina = 100;
    }
    else{
        _stamina = staminaInput;
    }
}

int GamePlayer::getStamina() {
    return _stamina;
}

void GamePlayer::setGold(double goldInput) {
    if(goldInput < 0){
        _gold = 0;
    }
    else if(goldInput > 100){
        _gold = 100;
    }
    else{
        _gold = goldInput;
    }
}

double GamePlayer::getGold() {
    return _gold;
}

void GamePlayer::setEffect(string effectInput) {
    _effect = effectInput;
}

string GamePlayer::getEffect() {
    return _effect;
}

void GamePlayer::printInventory() {

    for(int i = 0; i < _MAX_CANDY_AMOUNT; i += 3) {
        string first = _inventory[i].name;
        string second = _inventory[i + 1].name;
        string third = _inventory[i + 2].name;

        if(first.empty()) first = "Empty";
        if(second.empty()) second = "Empty";
        if(third.empty()) third = "Empty";

        cout << "|[" << first << "]|[" << second << "]|[" << third << "]|" << endl;
    }
}
Candy GamePlayer::findCandyInInventory(string candy_name){

    for(int i = 0; i < _MAX_CANDY_AMOUNT; i++) {

        if(candy_name == _inventory[i].name){

            return _inventory[i];
        }
    }
    return Candy{"", "", "", 0.0, "", 0.0};
}
bool GamePlayer::addCandyToInventory(Candy candy){

    if(_candy_amount < _MAX_CANDY_AMOUNT ) {

        _inventory[_candy_amount] = candy;
        _candy_amount++;

        return true;
    }
    else {
        return false;
    }
}
bool GamePlayer::removeCandyFromInventory(string candy_name){

    for (int i = 0; i < _candy_amount; i++){

        if(_inventory[i].name == candy_name){
            //shift
            for (int j = i; j < _candy_amount - 1; j++){
                _inventory[j] = _inventory[j+1];
            }
            //decrament size
            _candy_amount--;

            //last candy = empty
            _inventory[_candy_amount] = {"", "", "", 0.0, "", 0.0};

            return true;
        }
    }
    return false;
}

bool GamePlayer::validCandySelection(Candy candy){
    for(int i = 0; i < _candy_amount; i++){
        if (_inventory[i].name == candy.name){
            return true;
        }
    }
    return false;
}

bool GamePlayer::setPlayerPosition(int new_position)
{
    
    if (new_position >= 0 && new_position <= 83)
    {
        _player_position = new_position;
        return true;
    }
    else if (new_position < 0) {
        _player_position = 0;
        return true;
    }
    else {
        _player_position = 82;
        return true;
    }

    return false;
}

void GamePlayer::setPrevPos(int prev_pos){
    _prev_pos = prev_pos;
    if(_prev_pos < 0){
        _prev_pos = 0;
    }
}

int GamePlayer::getPrevPos(){
    return _prev_pos;
}

int GamePlayer::getPlayerPosition() {
    return _player_position;
}

void GamePlayer::setPlayerName(string name){
    player_name = name;
}
void GamePlayer::setCharacterName(string name){
    character_name = name;
}

string GamePlayer::getPlayerName(){
    return player_name;
}

string GamePlayer::getCharacterName(){
    return character_name;
}

void GamePlayer::printStats(){
    cout << endl;
    cout << "Your stats are: "<< endl;
    cout << endl;
    cout << "=============================================="<<endl;
    cout << endl;
    cout << "Player name: " << player_name << endl;
    cout <<"Character choice: " << character_name << endl;
    cout <<"Stamina: " << _stamina << endl;
    cout <<"Gold: " << _gold << endl;
    cout << "Candies: "<< endl;

    printInventory();

    cout << endl;
    cout << "=============================================="<<endl;
    cout << endl;

}

void GamePlayer::movePlayerBySpaces(int spaces){
    int i = 0;
    _prev_pos = _player_position;
    if(spaces > 0){
        while(i < spaces){
            _player_position++;
            i++;
            if(_player_position > 83){
                _player_position = 83;
            }
        }
    }
    else if (spaces < 0){
        while(i < (-spaces)-1){
            _player_position--;
            i++;
            if(_player_position < 0){
                _player_position = 0;
            }
        }
    }
}
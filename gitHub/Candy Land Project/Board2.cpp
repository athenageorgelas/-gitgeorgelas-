// CSCI1300 Fall 2023 Project 2
// Author: Athena Georgelas
// Recitation: 102 - Athena Georgelas
//Date: Dec 5, 2023

#include <iostream>
#include "Board2.h"

Board::Board()
{
    resetBoard();

    vector<Candy> canD = readCandy("candies.txt");

    int h1 = rand() % 28;
    //hidden treasure one
    int h2 = (rand() % 27)+28;
    //hidden treasure two
    int h3 = (rand() % 28)+55;
    //hidden treasure three
    //hidden treasure spot possibilities evenly distributed

    _tiles[h1].treasure = true;
    _tiles[h2].treasure = true;
    _tiles[h3].treasure = true;


    int p1 = rand() % 28;
    while(_tiles[p1].treasure == true){
        p1 = rand() % 28;
    }
 
    while(_tiles[p1].color != MAGENTA) p1--;

    stores[0] = Store("Wonderful Candies", p1);
    stores[0].addCandyToStore(canD);


    int p2 = (rand() % 27) + 28;

    while(_tiles[p2].treasure == true){
        p2 = (rand() % 27) + 28;
    }
 
    while(_tiles[p2].color != GREEN) p2--;
    stores[1] = Store("Willy Wonka's", p2);
    stores[1].addCandyToStore(canD);

    int p3 = (rand() % 28) + 55;

    while(_tiles[p3].treasure == true){
        p3 = (rand() % 28) + 55;
    }

    while(_tiles[p3].color != BLUE) p3--;
    stores[2] = Store("Colorful", p3);
    stores[2].addCandyToStore(canD);


    string types[] = {"Shortcut", "Ice Cream Stop", "Gumdrop Forest", "Gingerbread House"};
    vector<int> chosen_tiles;
    int count = 0;
    while(count < 4){

        int pos = rand() % _BOARD_SIZE;

        while(pos == p1 || pos == p2 || pos == p3){
            pos = rand() % _BOARD_SIZE;
            //make sure special tiles and shops not on the same tile
            //dont need to check for hidden treasures bc theres already no way a hidden treasure can be on the same tile as a store
        }

        for(int i = 0; i < chosen_tiles.size(); i++){
            if(pos == chosen_tiles[i]) continue;
            //chosen tiles must have a unique position
        }

        chosen_tiles.push_back(pos);
        _tiles[pos].tile_type = types[count];
        count++;
    }

    count = 0;
    while(count < 3){
        int pos = rand() % _BOARD_SIZE;

        if(_tiles[pos].treasure) continue;
        //checks if there is already a treasure at that tile then it skips over the rest and restarts the loop to create a new number


        _tiles[pos].treasure = true;
        count++;
    }

    current_turn = 0;
    //initializes to false

}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;

    string special_type[4] = {"Shortcut", "Ice Cream Stop", "Gumdrop Forest", "Gingerbread House"};

    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];

        int p = rand() % 4;

        if (p == 0){
            //25% chance a color will be special
            int p2 = rand() % 4;
            //4 types of special tiles which the game loops through

            new_tile = {current_color, special_type[p2]};
            //set this tile to the random special type
        }
        else{
            new_tile = {current_color, "regular tile"};
        }

        _tiles[i] = new_tile;
        //creates a tile struct randomly then sets tile of current position to this struct
    }

    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;


    players[0].setPlayerPosition(0);
    players[1].setPlayerPosition(0);

}

void Board::displayTile(int position)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color;
    int count = 0;
    if (position == players[0].getPlayerPosition())
    {
        cout << "1";
        count++;
    }
    if (position == players[1].getPlayerPosition()){
        cout << "2";
        count++;
    }

    if(count == 0) cout << "   ";
    else if(count == 1) cout << "  ";
    else cout << " ";


    cout << RESET;
}

void Board::displayBoard()
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}


int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

bool Board::playRockPaperScissors() {

    cout << "Enter r, p, or s"<<endl;

    string choice1;
    getline(cin, choice1);

    while (choice1 != "r" && choice1 != "p" && choice1 != "s"){
        cout << "Invalid input!"<<endl;
        getline(cin, choice1);   
    }

    string rps[3] = {"r", "p", "s"};
    int c = rand() % 3;

    cout << "You chose: " << choice1 << endl;
    cout << "The computer chose: " << rps[c] << endl;

    while (choice1 == rps[c]){

        cout << "Tie! Play again" << endl;

        cout << "Player 1: Enter r, p, or s"<<endl;
        getline(cin, choice1);  
        while (choice1 != "r" && choice1 != "p" && choice1 != "s"){
            cout << "Invalid input!"<<endl;
            getline(cin, choice1);   
        }

        c = rand() % 3;
        
    }

    if ((choice1 == "r" && rps[c] == "s") || (choice1 == "s" && rps[c] == "p") || (choice1 == "p" && rps[c] == "r")) {

        cout << "You have won! "<<endl;
        return true;

    }
    else{
        cout << "You have lost!"<< endl;
        return false;
    }
}



void Board::hiddenTreasureFunction(){

    cout << "Answer this riddle to unlock a hidden treasure: "<< endl;

    bool solved = RiddleFunction();

    if(solved){
            int p = rand() % 100;

        if(p < 30){
            //stamina refil
            int s = (rand() % 21)+10;

            players[current_turn].setStamina(players[current_turn].getStamina() + s);

            cout << "You landed on a Stamina Refill! you will be replenished with "<< s 
            << " units of stamina!"<< endl;

        }
        else if(p < 40){
            //gold windfall

            int g = (rand() % 21)+20;

            players[current_turn].setGold(players[current_turn].getGold() + g);

            cout << "You landed on a Gold Windfall! you will be given "<< g 
            << " gold coins!"<< endl;

        }
        else if(p < 70){
            //robbers repel

            cout << "You have received Robber's Repel! You now have immunity against gold robbery!"<< endl;

            players[current_turn].robbers_repel = true;
            
        }
        else if(p <100){
            //candy aquisition

            int r = rand() % 100;
            if(r < 30){
                cout << "You have received a Jellybean of Vigor! Use this candy to access a hidden treasure by solving a riddle." << endl;
                Candy new_candy = {"Jellybean of Vigor", "Using the Jellybean of Vigor, you can restore 50 units of stamina.", "stamina", 50.00, "magical", 0};
                players[current_turn].addCandyToInventory(new_candy);
            }
            else{
                cout << "You have received a Treasure Hunters Truffle! Use this candy to access a hidden treasure by solving a riddle." << endl;
                Candy new_candy = {"Treasure Hunters Truffle", "Use this candy to access a hidden treasure by solving a riddle.", "treasure", 0, "treasure", 0};
                players[current_turn].addCandyToInventory(new_candy);
            }
            
        }
    }

    
}

bool Board::RiddleFunction(){
    cout << "would you like to answer the riddle? (y/n)"<< endl;
    string choice;
    getline(cin, choice);

    while(choice != "y" && choice != "n"){
        cout << "Invalid choice."<<endl;

        getline(cin, choice);
    }
    if(choice == "y"){
        int r = rand() % (riddles.size()-1); //-1 because vector size is 1 more than the final index
            cout << riddles.at(r).riddle << endl;

            string ans;
            getline(cin, ans);

            if(ans == riddles.at(r).answer){
                cout << "Congrats! You have solved the riddle!"<< endl;
                return true;
            }
            cout << "You did not correctly answer the riddle"<< endl;
            return false;
    }
    else{
        return false;
    }
}

void Board::readRiddles(string file_name){

    ifstream file(file_name);

    if (!file.is_open()){
        cout << "Failed to open file"<< endl;
        return;
    }
    string line;
    while(getline(file, line)){
        stringstream ss(line);
        string  riddle_func, answer_func;

        if (getline(ss, riddle_func, '|') && getline(ss, answer_func, '|')){
            
            Riddle rnew;

            //create a new candy struct for function
            rnew.riddle = riddle_func;
            rnew.answer = answer_func;

            riddles.push_back(rnew);

        }
    }
    file.close();
}

void Board::readCharacter(string file_name){
    ifstream file(file_name);

    if (!file.is_open()){
        cout << "Failed to open file"<< endl;
        return;
    }
    string line;
    getline(file, line);
    while(getline(file, line)){
        stringstream ss(line);
        string name_func, stamina_func, gold_func, candies_func, candy_type_func, price_func, canD;

        if (getline(ss, name_func, '|') && getline(ss, stamina_func, '|') && getline(ss, gold_func, '|') && getline(ss, candies_func, '|') ){
            

            Character cnew;

            //create a new candy struct for function
            cnew.character_name = name_func;
            cnew.stamina = stoi(stamina_func);
            cnew.gold = stod(gold_func);

            stringstream sr(candies_func);
            vector<string> names;

            while(getline(sr, canD, ',')){
                names.push_back(canD);
            }
            for(int i = names.size(); i < 9; i++) {
                names.push_back("");
            }

            cnew.candies = names;

            characters.push_back(cnew);
        }
    }
    file.close();
}



Character Board::findCharacter(string name) {
    for (int i = 0; i < characters.size(); i++) {
        if (characters[i].character_name == name) {
            return characters[i];
        }
    }
    // If the character is not found, return a default character or handle it as needed.
    return Character{"", 0, 0., {}}; //
    
}

void Board::eraseCharacter(string name){
    int character_idx = -1;
    for(int i = 0; i < characters.size(); i++){
        if(characters[i].character_name == name){
            character_idx = i;
            break;
        }
    }

    if (character_idx != -1) {
        characters.erase(characters.begin() + character_idx);
        //start at zero in the characters vector then add the character index and erase
    }
}


bool Board::validCharName(string name){
    for(int i = 0; i < characters.size(); i++){
        if(characters[i].character_name == name){
            return true;
        }
    }

    return false;
}


Character Board::findChar(string name){
    for(int i = 0; i < characters.size(); i++){
        if(characters[i].character_name == name){
            return characters[i];
        }
    }

    return Character{"", 0, 0., {}};
}


void Board::initPlayer(int index, string name, Character ch, vector<Candy> candies){
    players[index].setPlayerName(name);
    players[index].setCharacterName(ch.character_name);
    players[index].setStamina(ch.stamina);
    players[index].setGold(ch.gold);

    for(int i = 0; i < ch.candies.size(); i++)
    {//loops through the characters candies
        for(int j = 0; j < candies.size(); j++)
        {//loops through the actual vector of loaded candies size
            if(ch.candies[i] == candies[j].name)
            {   //if they equal then add that candy struct to inventory
                players[index].addCandyToInventory(candies[j]);
            }
        }

    }
}


void Board::calamity(){
    int p = rand() % 100;


    if(p < 30){
        //candy bandits
        int t = rand() % 10;
        players[current_turn].setGold(players[current_turn].getGold() - (t+1));
        cout <<  "Oh no! Candy Bandits have swiped your gold coins!"<< endl;
        cout << "You have lost "<< t+1 << " gold coins."<<endl;
    }
    else if(p < 65){
        cout<<"Oh dear! You got lost in the lollipop labyrinth! You might lose a turn!"<<endl;
        cout << "Player rock, paper, scissors and you could win it back!"<<endl;
        bool win = playRockPaperScissors();
        if(!win){
            players[current_turn].lose_turn = true; 
            cout << "You lose a turn."<<endl;
        }
    }
    else if(p < 80){
        //avalanche
        cout << "Watch out! A candy avalanche has struck!"<< endl 
        << "You could lose your stamina!"<<endl
        << "Play rock, paper, scissors and win it back."<<endl;
        bool win = playRockPaperScissors();
        if(!win){
            int r = rand() % 5;
            players[current_turn].setStamina(players[current_turn].getStamina() - (r+6));
            cout << "You lose "<< r+6 << " units of stamina." << endl;
        }
    }
    else {
        //trap
        cout << "Oops! You are stuck in a sticky taffy trap!" << endl
        << "If you use a magical candy, you wont lose a turn."<< endl;

        cout << "Would you like to use a magical candy? (y,n)"<<endl;
        string c;
        getline(cin, c);
        bool valid = false; 

        if(c == "y" || c == "n"){
            valid = true;
        }

        while(!valid){
            cout << "Invalid input."<< endl;
            getline(cin, c);
            
            if(c == "y" || c == "n") {
                valid = true;
            }
        }

        if(c == "y"){
            if(players[current_turn]._candy_amount > 0) {
                bool found = false; 
                for (int i = 0; i < players[current_turn]._MAX_CANDY_AMOUNT;i++){

                    if(players[current_turn]._inventory[i].candy_type == "magical"){
                        players[current_turn]._inventory[i] = {};
                        players[current_turn]._candy_amount--;
                        found = true;
                    }
                    if(found) {
                        cout << "You gained your turn back!" << endl;
                        return;
                    }
                }
                if(!found){
                    cout << "You do not have a magical candy. You lose a turn." << endl; 
                    players[current_turn].lose_turn = true;
                }
            }
            else {
                cout << "You do not have any candy and lose a turn."<< endl;
                players[current_turn].lose_turn = true;

            }
        }
        else{
            players[current_turn].lose_turn = true;
            cout << "You lose a turn."<<endl;
        }
            
    }
}



void Board::printCharacters(){
    for(int x = 0; x < characters.size(); x++){
        cout << "Name: " << characters[x].character_name << endl;
        cout << "Stamina: " << characters[x].stamina << endl;
        cout << "Gold: " << characters[x].gold << endl;

        for(int i = 0; i < 9; i += 3) {
            string first = characters[x].candies[i];
            string second = characters[x].candies[i + 1];
            string third = characters[x].candies[i + 2];

            if(first.empty()) first = "Empty";
            if(second.empty()) second = "Empty";
            if(third.empty()) third = "Empty";

            cout << "|[" << first << "]|[" << second << "]|[" << third << "]|" << endl;
        }
    }
}

void Board::printMenu(){
    cout << "1. Draw a card"<< endl
         << "2. Use candy"<< endl
         << "3. Show player stats"<<endl;
}



void Board::drawCard(){

    players[current_turn].setPrevPos(players[current_turn].getPlayerPosition());

    double p1 = rand() % 10;
    bool dub; 
    if(p1 < 4){
        dub = true;
    }
    else {
        dub = false;
    }

    Card card_obj = {COLORS[rand() % 3], dub};

    
    int new_pos;

    for(new_pos = players[current_turn].getPlayerPosition() + 1; 
    _tiles[new_pos].color != card_obj.color && new_pos <= _BOARD_SIZE; new_pos++);
    //start at the position in front of the character, if that doesnt = the color then go forwards one more and so on until it equals
    //if they encounter the board size they stop there

    
    //loops until colors match
    if(dub){
        new_pos += 3;
        //add three to make it the next tile of that color
        if(new_pos >= 83){
            new_pos = 82;
        }
        if(_tiles[new_pos].color == MAGENTA){
            cout << "You drew a double magenta card!"<< endl;
        }
        else if(_tiles[new_pos].color == BLUE){
            cout << "You drew a double blue card!"<< endl;
        }
        else if(_tiles[new_pos].color == GREEN){
            cout << "You drew a double green card!"<< endl;
        }
        
    }
    else{
        if(_tiles[new_pos].color == MAGENTA){
            cout << "You drew a single magenta card!"<< endl;
        }
        else if(_tiles[new_pos].color == BLUE){
            cout << "You drew a single blue card!"<< endl;
        }
        else if(_tiles[new_pos].color == GREEN){
            cout << "You drew a single green card!"<< endl;
        }
    }
    if(_tiles[new_pos].baracade == true){
        cout << "You encountered a baracade and will lose"<<endl;
        _tiles[new_pos].baracade = false;
        
        int turns = rand() % 1;
        if(turns == 0){
            cout << " one turn!"<<endl;
            players[current_turn].lose_turn = true;
        }
        else{
            cout << " two turns!"<<endl;
            players[current_turn].lose_two_turn = true;
        }
        
        
    }
    else{
        players[current_turn].setPlayerPosition(new_pos);
    }
    


    for(int i = 0; i< _BOARD_SIZE; i++ ){
        if(stores[i].getPosition() == players[current_turn].getPlayerPosition()){
            cout << "You have come across the "<< stores[i].store_name_ <<" Store!" << endl;
            players[current_turn] = stores[i].sell(players[current_turn]);

            if (players[current_turn].getPlayerPosition() == players[!current_turn].getPlayerPosition()){
                
                

                cout << "You have landed on the same tile as "<< players[!current_turn].getPlayerName();
                if(players[current_turn].robbers_repel){
                    cout << ". They tried to rob you, but you have Robbers Repel and narrowly escaped!"<< endl;
                    cout << "Your opponent will be moved back by one tile." << endl;
                    players[!current_turn].setPlayerPosition(players[current_turn].getPlayerPosition()-1);
                    players[current_turn].robbers_repel = false;
                    return;
                }
                else{
                    int p = rand() % 10;
                    players[current_turn].setGold(players[current_turn].getGold()+ (p+6));
                    cout << "They have taken "<< p+6 << " gold from you!"<< endl; 
                }

                
            }
            return;

        }
    }
    
    if(_tiles[players[current_turn].getPlayerPosition()].treasure){

        hiddenTreasureFunction();

    }
    else{
        bool not_reg = specialTiles();

        if(!not_reg){ //if regular
            cout << "You have landed on a " << _tiles[players[current_turn].getPlayerPosition()].tile_type << endl; 
        }
            
    }

    if (players[current_turn].getPlayerPosition() == players[!current_turn].getPlayerPosition()){
                
        int p = rand() % 10;
        players[current_turn].setGold(players[current_turn].getGold()+ (p+6));

        cout << "You have landed on the same tile as "<< players[!current_turn].getPlayerName();
        if(players[current_turn].robbers_repel){
            cout << ". They tried to rob you, but you have Robbers Repel and narrowly escaped!"<< endl;
            cout << "Your opponent will be moved back by one tile." << endl;
            players[!current_turn].setPlayerPosition(players[current_turn].getPlayerPosition()-1);
            players[current_turn].robbers_repel = false;
            return;
        }

            cout << ". They have taken "<< p+6 << " gold from you!"<< endl; 
    }


}


bool Board::specialTiles(){
    Tile current = _tiles[players[current_turn].getPlayerPosition()];

    if(current.tile_type == "Shortcut"){

        cout << "There is a secret passage and you move forward 4 spaces."<<endl;
        players[current_turn].movePlayerBySpaces(4);
        if(_tiles[players[current_turn].getPlayerPosition()].baracade == true){
            cout << "You encountered a baracade and will lose"<<endl;
            _tiles[players[current_turn].getPlayerPosition()].baracade = false;
            int turns = rand() % 1;
            if(turns == 0){
                cout << " one turn!"<<endl;
                players[current_turn].lose_turn = true;
            }
            else{
                cout << " two turns!"<<endl;
                players[current_turn].lose_two_turn = true;
            }  
        }
        
        return true;

    }
    else if(current.tile_type == "Ice Cream Stop"){

        cout << "You have landed on an Ice Cream Stop tile, you gain an extra turn!"<< endl;
        cout<< endl;
       
        players[!current_turn].lose_turn = true;
        return true;

    }
    else if(current.tile_type == "Gumdrop Forest"){

        cout <<"You got lost in the Gumdrop Forest and will move back 3 spaces."<<endl;

        players[current_turn].movePlayerBySpaces(-4);

        double g = rand() % 6;
        players[current_turn].setGold(players[current_turn].getGold() - (g + 5));
 
        cout << "You have also lost "<< (g + 5) << " gold in the process!"<< endl;


        if(_tiles[players[current_turn].getPlayerPosition()].baracade == true){
            cout << "You encountered a baracade and will lose"<<endl;
            _tiles[players[current_turn].getPlayerPosition()].baracade = false;
            int turns = rand() % 1;
            if(turns == 0){
                cout << " one turn!"<<endl;
                players[current_turn].lose_turn = true;
            }
            else{
                cout << " two turns!"<<endl;
                players[current_turn].lose_two_turn = true;
            }  
        }

        return true;

    }
    else if(current.tile_type == "Gingerbread House"){

        cout << "You came across the Gingerbread House and will move back to your previous position."<< endl;

            players[current_turn].setPlayerPosition(players[current_turn].getPrevPos());

        if(players[current_turn]._candy_amount > 0) {
            for (int i = 0; i < players[current_turn]._MAX_CANDY_AMOUNT; i++){
                
                if(players[current_turn]._inventory[i].effect_type == "immunity"){
                    players[current_turn]._inventory[i] = {};
                    players[current_turn]._candy_amount--;
                    cout << "You also lost one of your precious immunity candies."<< endl;
                    return true;
                }
            }
        }
        if(_tiles[players[current_turn].getPlayerPosition()].baracade == true){
            cout << "You encountered a baracade and will lose"<<endl;
            _tiles[players[current_turn].getPlayerPosition()].baracade = false;
            int turns = rand() % 1;
            if(turns == 0){
                cout << " one turn!"<<endl;
                players[current_turn].lose_turn = true;
            }
            else{
                cout << " two turns!"<<endl;
                players[current_turn].lose_two_turn = true;
            }  
        }
        return true;
    }
    else {
        int p = rand() % 100;
        if(p < 40){
            calamity();
            return true;
        }
    }
    return false;
}



void Board::useCandy(){

    if(players[current_turn]._candy_amount == 0){
        cout << "You do not have any candy in your inventory."<<endl;
        printMenu();
        return;
    }

    for(int i = 0; i < players[current_turn]._candy_amount; i++){
        cout << players[current_turn]._inventory[i].name<< " : "
        << players[current_turn]._inventory[i].description <<" : "
        <<players[current_turn]._inventory[i].candy_type<<endl;
    }
    cout << "Here are your candies. Which candy would you like to use? (press 0 to exit)"<< endl;

    string c;
    getline(cin, c);

    if(c == "0"){
        cout << "Safe Travels!"<< endl;
        return;
    }
    Candy candy = players[current_turn].findCandyInInventory(c);

    bool valid = players[current_turn].validCandySelection(candy);

    while(!valid){
        cout << "invalid choice."<<endl;

        getline(cin, c);

        candy = players[current_turn].findCandyInInventory(c);

        valid = players[current_turn].validCandySelection(candy);
    }


    if(candy.candy_type == "poison"){

            for(Candy can : players[!current_turn]._inventory)
                if(can.candy_type == "immunity"){
                    int effect = 0;
                    if(candy.effect_value == -10){
                        effect += 1;
                    }
                    else if(candy.effect_value == -15){
                        effect += 2;
                    }
                    else if(candy.effect_value == -20){
                        effect += 3;
                    }
                    if(can.effect_value >= effect){
                        cout << players[!current_turn].getPlayerName() << " had an immunity candy and narrowly escaped your blow!"<<endl;
                        players[!current_turn].removeCandyFromInventory(can.name);
                        players[current_turn].removeCandyFromInventory(c);

                            printMenu();
                            return;
                            //player has used immunity to counterract
                    }
                    else{
                        //use on opponent
                        players[!current_turn].setStamina(players[!current_turn].getStamina() + candy.effect_value);
                    }
                }
            else{
                //use on opponent
                players[!current_turn].setStamina(players[!current_turn].getStamina() + candy.effect_value);
            }
    }
    else if(candy.effect_type == "treasure"){
        bool solved = RiddleFunction();
        if(solved){
            hiddenTreasureFunction();
        }
    }
    else if(candy.effect_type == "magical"){
        players[current_turn].setStamina(players[current_turn].getStamina() + candy.effect_value);
    }
    else if(candy.candy_type == "gummy"){//turns 

        _tiles[players[current_turn].getPlayerPosition()].baracade = true;
        cout << "You have created a baricade on this tile. Anyone who lands on this tile will lose turns!"<< endl;

    }


    bool t = players[current_turn].removeCandyFromInventory(c);
    if(t){
        if(candy.effect_value < 0){
            cout << "You have used "<< c << " on your opponent."<<endl;
        }
        else{
            cout << "You have used "<< c << " on yourself."<<endl;
        }
        
        players[current_turn]._candy_amount--;

        printMenu();
    }
    else{
        cout << "could notremove from inventory"<<endl;
        //this is a debug check 

        printMenu();
    }
    

}


int Board::finishedGame(){
    if(players[0].getPlayerPosition() == _BOARD_SIZE-1 ){
        return 3;
    }
    else if(players[1].getPlayerPosition() == _BOARD_SIZE-1){
        return 4;
    }
    else{
        return 5;
    }
}

void Board::finalScreen(GamePlayer players){
    cout << endl;
    cout << "Congradulations "<<players.getPlayerName()<<"! You completed the map!"<<endl;
    cout << endl;
    cout << "==========================================="<<endl;
    cout << endl;
    players.printStats();
    cout << endl;
    cout << "==========================================="<<endl;

    winnerToFile(players);
}

void Board::winnerToFile(GamePlayer players){

    ofstream winner("Winner.txt", ios::app);

    if(winner.is_open()){
        winner << "The winner was: "<< players.getPlayerName()<<endl;
        winner<< "Their character was: "<< players.getCharacterName() <<endl;
        winner<< "Their gold left was: "<< players.getGold()<<endl;
        winner<< "Their stamina left was: "<< players.getStamina()<<endl;
        winner<< "Their final inventory left was: "<<endl;
        for(int i = 0; i < players._candy_amount;i++){
            if(players._inventory[i].name != ""){
                winner << players._inventory[i].name<< " : " << players._inventory[i].description << endl;
            }
        }
        winner << endl;
        winner << endl;
        winner << endl;
        winner << endl;
        winner<< "Next Game: "<<endl;

        winner.close();
        
    }
    else{
        cout << "Failed to open file."<<endl;
    }
}


void Board::play(){
    if(players[current_turn].lose_turn) {
        players[current_turn].lose_turn = false; 
        current_turn = !current_turn;
        return;
    }

    cout << "It's " << players[current_turn].getPlayerName() << "'s turn" << endl;
    displayBoard();
    printMenu();

    bool end_turn = false;
    while(!end_turn){
        int input = isValidChoice("", 1, 3);

        switch (input){
            case 1:
                drawCard();
                players[current_turn].setStamina(players[current_turn].getStamina()-1);
                if(players[!current_turn].lose_two_turn){
                    play();
                    players[!current_turn].lose_two_turn = false;
                }
                end_turn = true;
                break;

            case 2:
                useCandy();
                break;

            case 3:
                players[current_turn].printStats();
                break;
        }
    }

    int hail = rand() % 100;
    if(hail < 5){
        Board::marshmallowHailstorm();
    }


    players[current_turn].printStats();
    current_turn = !current_turn;
    
}

void Board::marshmallowHailstorm(){
    int t = rand() % 5;
    cout << "Oh no! A Marshmallow Hailstorm has rampaged its way through CandyLand. "<< endl
    << "All players were pushed backwards by "<< t+1 << " tiles."<<endl;
    players[!current_turn].movePlayerBySpaces(-(t+2));
    players[current_turn].movePlayerBySpaces(-(t+2));
}

vector<Candy> Board::readCandy(string file_name){

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
        string  name_func, effect_type, description_func, effect_value, candy_type_func, price_str_func;

        // Name|Description|Effect type|Effect value|Candy type|Price

        getline(ss, name_func, '|');
        getline(ss, effect_type, '|');
        getline(ss, description_func, '|');
        getline(ss, effect_value, '|');
        getline(ss, candy_type_func, '|');
        getline(ss, price_str_func, '|');
            
        Candy cnew;

        //create a new candy struct for function
        cnew.name = name_func;
        cnew.effect_type = effect_type;
        cnew.description = description_func;
        cnew.effect_value = stod(effect_value);
        cnew.candy_type = candy_type_func;
        cnew.price = stod(price_str_func);

        candies.push_back(cnew);

    } 
    file.close();
    return candies;

}
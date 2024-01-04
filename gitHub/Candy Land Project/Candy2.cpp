// CSCI1300 Fall 2023 Project 2
// Author: Athena Georgelas
// Recitation: 102 - Athena Georgelas
//Date: Dec 5, 2023

#include <iostream>
#include <string>
#include "Candy2.h"


Store::Store(){
    position = 0;
}

Store::Store(string store_name, int p){

    store_name_ = store_name;
    position = p;

}

void Store::readCandy(string file_name){

    ifstream file(file_name);

    if (!file.is_open()){
        cout << "Failed to open file"<< endl;
        return;
    }
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

}




void Store::displayCandiesInStore() const{

    if(candies.size() == 0) {
        cout << "no candies available."<<endl;
        return;
    }

    cout << "available candies: "<<endl;
    cout << endl;
    cout << "======================================================" << endl;
    for (int i = 0; i < candies.size(); i++){
        cout << "Name: " << candies[i].name << endl;
        cout << "Description: " << candies[i].description << endl;
        cout << "Type: " << candies[i].candy_type << endl;
        cout << "Price: " << candies[i].price << endl;
        cout << "======================================================" << endl;
    }

}


int Store::getPosition() const {
    return position;
}


void Store::setPosition(int p){
    position = p;
}

Candy Store::findCandyInStore(string name){
    for(int i = 0; i< candies.size();i++){
        if(candies.at(i).name == name){
            return candies.at(i);
        }
    }
    return {};
}

GamePlayer Store::substitution(GamePlayer p){
    cout << "Here is your inventory: "<<endl;
    p.printInventory();

    cout << "Would you still like to swap?"<< endl;

    string yn;
    getline(cin, yn);

    while(yn != "y" || yn != "n"){
        cout << "Invalid input." << endl;
        getline(cin, yn);
    }

    if(yn == "y"){
        displayCandiesInStore();
        cout << "Which candy would you like to swap?"<< endl; 
        string name;
        getline(cin, name);
        Candy choice = p.findCandyInInventory(name);
        bool valid = p.validCandySelection(choice);

        while(!valid){
            cout << "Invalid selection. Would you still like to swap? (y/n)"<<endl;

            getline(cin, yn);

            while(yn != "y" || yn != "n"){
                cout << "Invalid input." << endl;
                getline(cin, yn);
            }

            if(yn == "y"){
                cout << "Which candy would you like to swap?"<< endl; 

                getline(cin, name);
                Candy choice = p.findCandyInInventory(name);
                valid = p.validCandySelection(choice);
            }
            else{
                return p;
            }
        }

        displayCandiesInStore();
        cout << "Here are all the candies in the store, which candy would you like to add?" << endl;

        getline(cin, yn);

        while(yn != "y" || yn != "n"){
            cout << "Invalid input." << endl;
            getline(cin, yn);
        }

        if(yn == "y"){
            string newc;
            getline(cin, newc);
            Candy new_candy = findCandyInStore(newc);

            while(new_candy.name == ""){
                cout << "invalid input."<< endl;

                getline(cin, newc);
                new_candy = findCandyInStore(newc);
            }

            for(int i = 0; i < p._candy_amount; i++){
                if(p._inventory[i].name == choice.name){
                    p._inventory[i].name = new_candy.name;
                    p._inventory[i].candy_type = new_candy.candy_type;
                    p._inventory[i].description = new_candy.description;
                    p._inventory[i].effect_type = new_candy.effect_type;
                    p._inventory[i].effect_value = new_candy.effect_value;
                    p._inventory[i].price = new_candy.price;
                }
            }
            if(p.getGold() < new_candy.price){
                cout << "You dont have enough gold!" << endl;
                return p;
            }
            p.setGold(p.getGold() - new_candy.price);
            cout << "Safe travels!"<< endl;
            return p;
        }
    }
    else {
        cout << "Ok, you will now leave the store. Safe travels!"<< endl;
        return p;
    }
    return p;
}


GamePlayer Store::sell(GamePlayer p){
     
    if(p.getCandyAmount() == 9)
    {
        cout << "Inventory is full!" << endl;
        cout << "Would you like to swap?" << endl;
        string yn;
        getline(cin, yn);

        while(yn != "y" || yn != "n"){
            cout << "Invalid input." << endl;
            getline(cin, yn);
        }
        if(yn == "y"){
            p = substitution(p);
        }
        return p;
    } 

    //possibility of discount
    bool dis = discount();
    bool correct = false;
    if(dis){
        correct = unscramble();
    }
    if(!dis){//no discount or added val
        cout << "Choose one of the candies below (press '0' to exit):" << endl;
        string a;
        displayCandiesInStore();
        cout << endl;
        cout << "You have "<< p.getGold() << " gold coins."<<endl;

        getline(cin, a);

        if(a == "0"){
            cout << "Safe Travels!"<<endl;
            return p;
        }

        while(true){
            for(Candy c : candies)
            if(c.name == a){
                if(p.getGold() < c.price){
                    cout << "You dont have enough gold! Come back another time." << endl;
                    return p; 
                }

                p.addCandyToInventory(c);

                p.setGold(p.getGold() - c.price);

                cout << "Here is your updated inventory: "<<endl;
                cout << endl;
                p.printInventory();
                return p;
            }
            cout << "Invalid input!" << endl;
            getline(cin, a);
        }

    }
    else{
        //with discount
        cout << "Choose one of the candies below (press '0' to exit):" << endl;
        string a;
        displayCandiesInStore();
        cout << endl;
        cout << "You have "<< p.getGold() << " gold coins."<<endl;

        getline(cin, a);

        if(a == "0"){
            cout << "Safe Travels!"<<endl;
            return p;
        }

        while(true){
            if(correct){
                for(Candy c : candies)
                if(c.name == a){
                    if(p.getGold() < (c.price-(0.1*c.price))){
                        cout << "You dont have enough gold!" << endl;
                        return p;
                    }

                    p.addCandyToInventory(c);

                    p.setGold(p.getGold() - (c.price-(0.1*c.price)));

                    cout << "Here is your updated inventory: "<<endl;
                    cout << endl;
                    p.printInventory();
                    return p;
                }
                cout << "Invalid input!" << endl;
                getline(cin, a);
            }
            else{
                for(Candy c : candies)
                if(c.name == a){
                    if(p.getGold() < (c.price+(0.1*c.price))){
                        cout << "You dont have enough gold!" << endl;
                        return p;
                    }

                    p.addCandyToInventory(c);

                    p.setGold(p.getGold() - (c.price-(0.1*c.price)));

                    cout << "Here is your updated inventory: "<<endl;
                    cout << endl;
                    p.printInventory();
                    return p;
                }
                cout << "Invalid input!" << endl;
                getline(cin, a);
            }
                
        }
    }

}

void Store::addCandyToStore(vector<Candy> cand){
    candies.clear();
    for(int j = 0; j < 3; j++){
        int r = rand() % cand.size();
        if(candies.empty() == false){
            while(candies.at(candies.size()-1).name == cand.at(r).name) r = rand() % cand.size();
        }
        
        candies.push_back(cand.at(r));
    }

}

bool Store::discount(){
    int d = rand() % 100;
    if(d < 25){
        return true;
    }
    else return false;
}

bool Store::unscramble(){

     cout << "Unscramble this candy-related word to receive a discount!"<< endl;

        int w = rand() % 4;
        if(w == 1){
            cout << "The words is 'yandc' (enter in undercase!)"<< endl;
            
            string a;
            getline(cin, a);

            if(a == "candy"){
                cout << "You receive a 10 percent discount!"<<endl;
                return true;
            }
            else{
                cout << "You do not receive a discount and all prices increase by 10%!"<<endl;
                //inc by ten
                return false;
            }

        }
        else if(w == 2){
            cout << "The words is 'tewes' (enter in undercase!)"<< endl;
            
            string a;
            getline(cin, a);

            if(a == "sweet"){
                cout << "You receive a 10 percent discount!"<<endl;
                //dec by 10
                return true;
            }
            else{
                cout << "You do not receive a discount and all prices increase by 10%!"<<endl;
                //inc by ten
                return false;
            }

        }
        else if(w == 3){
            cout << "The words is 'rgasu' (enter in undercase!)"<< endl;
            
            string a;
            getline(cin, a);

            if(a == "sugar"){
                cout << "You receive a 10 percent discount!"<<endl;
                //dec by 10
                return true;
            }
            else{
                cout << "You do not receive a discount and all prices increase by 10%!"<<endl;
                //inc by ten
                return false;
            }

        }
        else if(w == 4){
            cout << "The words is 'muyym' (enter in undercase!)"<< endl;
            
            string a;
            getline(cin, a);

            if(a == "yummy"){
                cout << "You receive a 10 percent discount!"<<endl;
                //dec by 10
                return true;
            }
            else{
                cout << "You do not receive a discount and all prices increase by 10%!"<<endl;
                //inc by ten
                return false;
            }

        }
        return false;
    }
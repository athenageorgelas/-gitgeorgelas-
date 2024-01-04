#include <iostream>
#include <string>
using namespace std;


char shiftChar(char c, int shift) {
    if(c >= 'a' && c <= 'z'){//if lowercase alphabet letter, complete this:
        return ((((c - 'a') + (shift % 26))+26)%26) +'a'; 
        //return to user who calls function: letter- 'a' (26) in order to make a = 0, b = 1, c =...
        //add that to the shift value modulus 26 (if its more than 26 it will return to 1, 2, ...)
        //add 26 to account for decraments making final values negative
        //modulus the addition by 26 so if the final char is > 26 (> 'z'), wrap around back to 'a'
        //add back 'a' to the whole thing to allow correct ascii values 
        
    }

    return c; //if not a-z then return og value
}

int getMethod2ShiftAmount(const string key1) { //const to prevent modification of string
    //all cout statements should exist in the main function only
    int vowel_number = 0; //initialize vowel to 0 so can modify 
    //get the number of vowels (lower) in key1 using a for loop and incramenting the number of vowels.
    for (int i = 0; i < key1.length(); i++) { //loop for length of key1
        char c = key1[i]; //c is now the i'th letter in key1
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') { //invrament vowel_number each time the i'th character is a vowel
            vowel_number++;
        }
    }
    
    //get the length of the string using s.length() function
    int length = key1.length();
    
    //comput the shift value by adding together length and number of vowels in key1 modulus 26
    int shift_value = (length + vowel_number) % 26;

    return shift_value;
}

int getMethod3ShiftAmount(const string key1, const string key2) { //const prevents modification
//method 3 accounts for each similar character between key1 and key2
    int similar_characters = 0; //base = 0
    for (int i = 0; i < key1.length(); i++) { //loop for length of key2
        for (int j = 0; j < key2.length(); j++) { //loop for las long as j
            if (key1[i] == key2[j]) { //if any j value in key2 is = to an i value in key1, add 1 to similar characters
                similar_characters++;
            }
        }
    }
    if (similar_characters <= 26) { 
        return similar_characters;
    } else {
        return similar_characters % 26; //if the similar characters is greater than num of letter in alphabet then modulus 26 to start from 0, 1, 2, 3...
    }
}

char encryptChar(char c, int method_choice, string key1, string key2) {
    int shift = 0; //start shift valuue from 0
    //this function will calculate the shift value using different methods then it will pass it through shiftchar to ENcrament

    if (method_choice == 1) {
        shift = 1;
    } else if (method_choice == 2) {
        shift = getMethod2ShiftAmount(key1);
    } else if (method_choice == 3) {
        shift = getMethod3ShiftAmount(key1, key2);
    }
    else if (method_choice == 4) {

        for (int i = 0; i < c; i++) { 

            int method_4 = (i % 3) + 1; //calculate which one to use 

            if (method_4 == 1) {
                shift = 1;
            }
            else if (method_4 == 2) {

                shift = getMethod2ShiftAmount(key1);
            } 
            else if (method_4 == 3) {

                shift = getMethod3ShiftAmount(key1, key2);
            }
            return shiftChar(c, shift);
        }
    }

    return shiftChar(c, shift);

}

char decryptChar(char c, int method_choice, string key1, string key2) { //same but decrypting
    //to decrypt all will be negative and also passed through shift char but shift in the opposite direction (a -> z)
    int shift = 0;

    if (method_choice == 1) {
        shift = -1;
    } else if (method_choice == 2) {
        shift = -getMethod2ShiftAmount(key1);
    } else if (method_choice == 3) {
        shift = -getMethod3ShiftAmount(key1, key2);
    }
    else if (method_choice == 4) {

        for (int i = 0; i < c; i++) {

            int method_4 = (i % 3) + 1;

            if (method_4 == 1) {
                shift = -1;
            }
            else if (method_4 == 2) {

                shift = -getMethod2ShiftAmount(key1);
            } 
            else if (method_4 == 3) {

                shift = -getMethod3ShiftAmount(key1, key2);
            }
            return shiftChar(c, shift);
        }
    }

    return shiftChar(c, shift);

}

string decryptMessage(string message, int method_choice, string key1, string key2) {

    string returned_message = "";
    int j = message.length();

    if (method_choice == 1 || method_choice == 2 || method_choice == 3) {

        for (int i = 0; i < j; i++) {

            char c = message[i];
            
            returned_message += decryptChar(c, method_choice, key1, key2);
            
        }
    }
    else if (method_choice == 4) {

        int i = 0; 

        while (i < j) { //this simplifies the function


            char c = message[i]; //runs through i'th character in the phrase/word

            message[i] = decryptChar(message[i], 1, key1, key2);

            message[i + 1] = decryptChar(message[i + 1], 2, key1, key2);
            
            message[i + 2] = decryptChar(message[i + 2], 3, key1, key2);

            i += 3; //incrament 3 because technically passed through 3 characters

        }
        return message;
    }
    else {

        cout << "Invalid decryption method"<< endl;
        return message;

    }
    return returned_message;

}

string encryptMessage(string message, int method_choice, string key1, string key2) {

    string returned_message = "";
    int j = message.length();

    if (method_choice == 1 || method_choice == 2 || method_choice == 3) {

        for (int i = 0; i < j; i++) {

            char c = message[i];
            
            returned_message += encryptChar(c, method_choice, key1, key2);
            
        }
    }
    else if (method_choice == 4) {

        int i = 0; 

        while (i < j) {


            char c = message[i];

            message[i] = encryptChar(message[i], 1, key1, key2);

            message[i + 1] = encryptChar(message[i + 1], 2, key1, key2);
            
            message[i + 2] = encryptChar(message[i + 2], 3, key1, key2);

            i += 3;

        }
        return message;
    }
    else {

        cout << "Invalid encryption method"<< endl;
        return message;

    }
    return returned_message;

}

bool isValid(string choice) { //tests if the menu choice is valid

    if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6") {

        return true;

    }
    else {

        return false;

    }



}

bool isValidMethod(string method_choice) {
    if (method_choice == "1" || method_choice == "2" || method_choice == "3" || method_choice == "4") {

        return true;

    }
    else {

        return false;

    }
}


int main()
{

    string key1, key2, message;
    string method_choice = "";
    string choice = "";
    //each 




    while(choice != "6"){ 
        //present menu to the user
        cout << "Please input 1-6 followed by enter to navigate the menu:" << endl;
        cout << "1. Set Encryption Key 1" << endl;
        cout << "2. Set Encryption Key 2" << endl;
        cout << "3. Select Encryption Method" << endl;
        cout << "4. Encrypt Message" << endl;
        cout << "5. Decrypt Message" << endl;
        cout << "6. Exit Program" << endl;

        getline(cin, choice); //why getline? getline will account for characters and spaces (lakes an entire line)

        while (!isValid(choice)) { //while the choice is not valud
            
            cout << "Invalid input"<< endl;

            getline(cin, choice);
            //function will continuously return the option to add choice
        }

        //if else statements to consider each option
        if(choice == "1"){ 

            cout << "Enter key:" << endl;

            getline(cin, key1);

            while (key1.length() < 1) { //if the key1 is invalid according to writeup

                cout << "Invalid key"<< endl;
                cout << "Enter key:" << endl;
                getline(cin, key1); //prompt again

            }
            cout << "Successfully set encryption key1 to "<< key1 << endl; //if you can bypass or exit the while loop
        }
        else if(choice == "2"){ //same as 1 bbut with key 2

            cout << "Enter key:" << endl;

            getline(cin, key2);

            while (key2.length() < 1) {

                cout << "Invalid key"<< endl;
                cout << "Enter key:" << endl;
                getline(cin, key2);

            }
            cout << "Successfully set encryption key2 to "<< key2 << endl;
            
        }
        else if(choice == "3"){
            //pompt the menu (1-4)
            cout << "Please input 1-4 to decide encryption technique." << endl
            << "1. Method1 only (shift by 1)" << endl
            << "2. Method2 only (shift by first key)" << endl 
            << "3. Method3 only (shift by both keys)" << endl
            << "4. Mix of Method1, Method2, Method3"<< endl;

            getline(cin, method_choice);

            while (!isValidMethod(method_choice)) { //if the choice was invalid
                cout << "Invalid encryption choice" << endl;
                getline(cin, method_choice); //prompt again 
            }
            cout << "Successfully set encryption type to "<< method_choice << endl; //if you bypass or exit while loop
        }
        else if(choice == "4"){
            if (key1 == "" || method_choice == "" || key2 == "" ) { //this means nothing was changed to any of these initialized variables
                cout << "You cannot do this until you set both keys and choose an encryption method"<< endl; //menu prompts again bc still in loop
            }
            else {
                cout << "Enter your message to encrypt:" << endl;
                getline(cin, message);
                int method = stoi(method_choice); //converts string to integer
                string encrypted = encryptMessage(message, method, key1, key2); //encrpyts the message

                cout << encrypted << endl; 
            }
            
        }
        else if(choice == "5"){

            if (key1 == "" || method_choice == "" || key2 == "" ) { //this means nothing was changed to any of these initialized variables
                cout << "You cannot do this until you set both keys and choose an encryption method"<< endl; //menu prompts again bc still in loop
            }
            else {
                cout << "Enter your message to decrypt:" << endl;
                getline(cin, message);
                int method = stoi(method_choice); //converts string to integer
                string decrypted = decryptMessage(message, method, key1, key2); //decrypts message

                cout << decrypted << endl;
            }
            
        }
        else if(choice == "6"){ //exit, because this is inside a while loop for not 6, then it will exit the while loop and return 0

            cout << "Goodbye."<< endl;
            
        }
    }

    return 0;
}

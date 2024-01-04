#include <iostream>
#include <string>
#include <limits>

using namespace std;
//encrypt shift char
char negShiftChar(char c, int shift) {
    if (c >= 'a' && c <= 'z') {
        for (int i = 0; i < shift; i++) {
            c++;
            if (c > 'z') {
                c = 'a';
            }
        }
    }
    else {

        return c;

    }
    return c;
}

//decrypt shiftchar
char posShiftChar(char c, int shift) {
    if (c >= 'a' && c <= 'z') {
        for (int i = 0; i < shift; i++) {
            c--;
            if (c < 'a') {
                c = 'z';
            }
        }
    }
    else {

        return c;

    }
    return c;
}

int getMethod2ShiftAmount(const string key1) {
    int vowel_number = 0;
    for (int i = 0; i < key1.length(); i++) {
        char c = key1[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' || c == '!' || c == '?' || c == ';' || c == ':') {
            vowel_number++;
        }
    }
    int length = key1.length();
    int shift_value = (length + vowel_number) % 26; // Get remainder so that if > 26 it will = 1
    return shift_value;
}

int getMethod3ShiftAmount(const string key1, const string key2) {
    int similar_characters = 0;
    for (int i = 0; i < key1.length(); i++) {
        for (int j = 0; j < key2.length(); j++) {
            if (key1[i] == key2[j]) {
                similar_characters++;
            }
        }
    }
    if (similar_characters <= 26) {
        return similar_characters;
    } else {
        return similar_characters % 26;
    }
}

//encrypting char
char encryptChar(char c, int method_choice, string key1, string key2) {
    int shift = 0;

    if (method_choice == 1) {
        shift = 1;
    } else if (method_choice == 2) {
        shift = getMethod2ShiftAmount(key1);
    } else if (method_choice == 3) {
        shift = getMethod3ShiftAmount(key1, key2);
    }
    else if (method_choice == 4) {

        for (int i = 0; i < c; i++) {

            int method_4 = (i % 3) + 1;

            if (method_4 == 1) {
                shift = 1;
            }
            else if (method_4 == 2) {

                shift = getMethod2ShiftAmount(key1);
            } 
            else if (method_4 == 3) {

                shift = getMethod3ShiftAmount(key1, key2);
            }
            return posShiftChar(c, shift);
        }
    }

    return posShiftChar(c, shift);

}

//decrypting char
char decryptChar(char c, int method_choice, string key1, string key2) {
    int shift = 0;

    if (method_choice == 1) {
        shift = 1;
    } else if (method_choice == 2) {
        shift = getMethod2ShiftAmount(key1);
    } else if (method_choice == 3) {
        shift = getMethod3ShiftAmount(key1, key2);
    }
    else if (method_choice == 4) {

        for (int i = 0; i < c; i++) {

            int method_4 = (i % 3) + 1;

            if (method_4 == 1) {
                shift = 1;
            }
            else if (method_4 == 2) {

                shift = getMethod2ShiftAmount(key1);
            } 
            else if (method_4 == 3) {

                shift = getMethod3ShiftAmount(key1, key2);
            }
            return negShiftChar(c, shift);
        }
    }

    return negShiftChar(c, shift);

}

//decrypting message
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

        while (i < j) {


            char c = message[i];

            message[i] = negShiftChar(c, 1);

            message[i + 1] = negShiftChar(message[i+1], getMethod2ShiftAmount(key1)); 
            
            message[i + 2] = negShiftChar(message[i+2], getMethod3ShiftAmount(key1, key2));

            i += 3;

        }
        return message;
    }
    else {

        cout << "Invalid decryption method"<< endl;
        return message;

    }
    return returned_message;

}

//encrypting message
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

            message[i] = posShiftChar(c, 1);

            message[i + 1] = posShiftChar(message[i+1], getMethod2ShiftAmount(key1)); 
            
            message[i + 2] = posShiftChar(message[i+2], getMethod3ShiftAmount(key1, key2));

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

int main() {
    string key1, key2, message;
    int method_choice = 0;
    int choice = 0;
    bool key_B = false;

    while (true) {
        cout << "Please input 1-6 followed by enter to navigate the menu:" << endl;
        cout << "1. Set Encryption Key 1" << endl;
        cout << "2. Set Encryption Key 2" << endl;
        cout << "3. Select Encryption Method" << endl;
        cout << "4. Encrypt Message" << endl;
        cout << "5. Decrypt Message" << endl;
        cout << "6. Exit Program" << endl;

        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please try again." << endl;
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Flush the buffer
            continue;
        }

        if (choice == 1 || choice == 2) {
            string key;
            while (true) {
                cout << "Enter key: " << endl;
                cin >> key;
                if (key.length() < 1) {
                    cout << "Invalid key. Please try again." << endl;
                } else {
                    if (choice == 1) {
                        key1 = key;
                        cout << "Successfully set encryption key1 to " << key1 << endl;
                    } else {
                        key2 = key;
                        cout << "Successfully set encryption key2 to " << key2 << endl;
                    }
                    key_B = true;
                    break;
                }
            }
        } else if (choice == 3) {
            if (!key_B) {
                cout << "You cannot do this until you set both keys." << endl;
                continue;
            }
            cout << "Please input 1-4 to decide encryption technique." << endl;
            cout << "1. Method1 only (shift by 1)" << endl;
            cout << "2. Method2 only (shift by first key)" << endl;
            cout << "3. Method3 only (shift by both keys)" << endl;
            cout << "4. Mix of Method1, Method2, Method3" << endl;

            cin >> method_choice;

            if (cin.fail() || method_choice < 1 || method_choice > 4) {
                cout << "Invalid encryption choice" << endl;
                cin.clear(); // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Flush the buffer
                continue;
            } else {
                cout << "Successfully set encryption type to " << method_choice << endl;
            }
        } else if (choice == 4) {
            if (!key_B || method_choice == 0) {
                cout << "You cannot do this until you set both keys and choose an encryption method" << endl;
            } else {
                cout << "Enter your message to encrypt: "<< endl;
                cin.ignore();
                getline(cin, message);

                //encryption
                cout << "Encrypted message: " << encryptMessage(message, method_choice, key1, key2) << endl;
            }
        } else if (choice == 5) {
            if (!key_B || method_choice == 0) {
                cout << "You cannot do this until you set both keys and choose an encryption method" << endl;
            } else {
                cout << "Enter your message to decrypt: "<< endl;
                cin.ignore();
                getline(cin, message);

                // decryption
                decryptMessage(message, method_choice, key1, key2);

                cout << "Decrypted message: " << decryptMessage(message, method_choice, key1, key2) << endl;
            }
        } else if (choice == 6) {
            cout << "Goodbye." << endl;
            break;
        } else {
            cout << "Invalid input" << endl;
        }
    }

    return 0;
}
#include <iostream>

using namespace std;


//calculates expenses of user
//user can enter what kind of expense they are tracking and the code will run until the user says "exit"
//code then calculates and saves total
int expenseTracker() {
    int gr = 0; 
    int ent = 0; 
    int edu = 0;
    string category = "";
    int amount; int total;
    while (category != "exit"){
        cout << "Enter category (Groceries, Entertainment, Education, or Exit)" << endl;
        cin >> category;
        cout << "Enter the expense amount" << endl;
        cin >> amount;
        if (category == "Groceries") {
            gr += amount;
        }
        else if (category == "entertainment"){
            ent += amount;
        }
        else if (category == "Education"){
            edu += amount;
        }
        else {
            cout << "Please enter a valid amount." << endl;
        }
        total = gr + ent + edu;
        cout << "expenses" << endl;
        cout << "Groceries $" << gr << endl;
        cout << "Entertainment $" << ent << endl;
        cout << "Education $" << edu << endl;
        return total;

    }


}
//main calls the expense tracker function
//returns to user their expense
int main() {
    int total = expenseTracker();
    cout << "Total expense for the day" << total << endl;

    return 0;
}
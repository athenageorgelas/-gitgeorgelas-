#include <iostream>
using namespace std;


//this code will calculate the tax of an individual based on their income and age
int main() {

    double age;
    double income; //initialize variables

     cout << "What is your age?" << endl; //add values to variables
     
     cin >> age;

     cout <<"What is your income?" << endl;

     cin >> income;

     if (age < 60 && income < 50000) 
     {
        double tax = 0.10*income; //take 10% of income

        cout << "You are required to pay $"<<tax<<" in taxes"<< endl;
     }
     else if (age < 60 && income >= 50000)
     {
        double tax = 0.20*income; //take 20% of income

        cout << "You are required to pay $"<<tax<<" in taxes"<< endl;
     }
     else if (age >= 60 && income < 20000)
     {
        double tax = income; //no income tax
        cout << "You are not required to pay taxes"<< endl;
     }
     else if (age >= 60 && income >= 20000)
     {
        double tax = 0.05*income; //5% income tax
        cout << "You are required to pay $"<<tax<<" in taxes" << endl;
     }
     else if (age <= 0 || income <= 0)
     {
        cout << "Neither age nor income can be zero"<< endl;
     }
    

    return 0;
}
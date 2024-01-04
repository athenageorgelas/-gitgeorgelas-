

#include <iostream>
#include <iomanip>

using namespace std;

/*
this code calculates the users cost when purchasing ducks
this particular store gives discounts based on the amount of ducks bought
for example: if the user buys 20 ducks or less, each duck costs 50 cents-
but if the user buys between 20 and 100 ducks, they get a 10% discount!
*/

double calculate(double num){
    if(num <= 20){
        return num*0.50;
    }
    else if(num <= 100){
        return (num*0.50)-(0.10*(num*0.50));
    }
    else if(num <= 500){
        return (num*0.50)-(0.20*(num*0.50));
    }
    else{
        return (num*0.50)-(0.50*(num*0.50));
    }
}

int main(){
    cout << "How many ducks would you like to order?"<<endl;
    double ducks;
    cin >> ducks;
    if(ducks < 0){
        cout <<"Please enter a valid input."<<endl;
        return 0;
    }
    double price = calculate(ducks);
    cout << "Your total is $"<<fixed << setprecision(2)<< price <<endl;
    return 0;
}
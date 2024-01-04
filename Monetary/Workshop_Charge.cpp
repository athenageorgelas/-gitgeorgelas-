// CSCI 1300 Fall 2023
// Author: Athena Georgelas
// TA: Anush
// Question #3

#include <iostream>
#include <iomanip>

using namespace std;

//wrkshop add ons are $50.00
// Student Pass	35.50
// Professional Pass	75.25
// VIP Pass	150.75
// Speaker Pass	200.50
double cost(string type){
    if(type == "S"){
        return 35.50;
    }
    else if (type == "P"){
        return 75.25;
    }
    else if (type == "V"){
        return 150.75;
    }
    else if (type == "K"){
        return 200.50;
    }
    else{
        cout << "Invalid."<<endl;
        return 0;
    }
}

string passName(string type){
    if(type == "S"){
        return "Student";
    }
    else if(type == "P"){
        return "Professional";
    }
    else if(type == "V"){
        return "VIP";
    }
    else if(type == "K"){
        return "Speaker";
    }
}

int main(){
    cout << "Enter the desired pass type (S for Student, P for Professional, V for VIP, K for Speaker): ";
    string type;
    cin >> type;
    if(type != "S" && type != "P" && type != "K" && type != "V"){
        cout << endl;
        cout << "Please enter valid input."<<endl;
        return 0;
    }
    string passname = passName(type);

    cout << endl;


    cout << "Enter the number of workshop add-ons: ";
    double addons;
    cin >> addons;

    if(addons < 0){
        cout << endl;
        cout <<"Please enter a non-negative number of workshops."<<endl;
        return 0;
    }

    cout << endl;

    cout << "Enter your budget: $";
    double budget;
    cin >> budget;

    cout << endl;

    double charge = cost(type)+(addons*50.00);
    if(charge > budget){
        cout << "Pass purchase failed. Insufficient funds."<<endl;
        return 0;
    }
    else{
        cout << "Pass purchase successful! Pass type: "
        << passname <<", Workshops: "<< addons 
        <<", Total cost: $"<<charge << ", Remaining budget: $"
        << (budget-charge)<<endl;
        return 0;
    }

}
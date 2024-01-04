
#include <iostream>

using namespace std;

/*
predicts revenue given the current revenue and number of years forward
*/
int predictRevenue(int current_revenue, int years){

    //nextYearRev = 2 * currentYearRev + 5

    //base case
    if(years == 0){
        return current_revenue;
    }
    else{
        int futureRev = 2 * current_revenue + 5;
        return predictRevenue(futureRev, years-1);
    }
    //return predicted rev after years
}
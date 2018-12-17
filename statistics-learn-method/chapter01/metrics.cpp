/**
 * Author: xiaoran
 * Time: 2018-12-13
 */ 

#include "metrics.h"
#include <vector>
#include <iostream>
using namespace std;

int main()
{

    vector<int> y_true = {1,1,1,0,0,0};
    vector<int> y_pred = {1,0,1,0,0,1};

    cout<<cat::zero_one_loss(y_true, y_pred)<<endl;
    cout<<cat::accuracy_score(y_true, y_pred)<<endl;
    
    vector<double> y_true1 = {1.1,1.2,1.3,2,3,4};
    vector<double> y_pred1 = {1,0,1,2,3,4};
    cout<<cat::mean_absolute_loss(y_true1, y_pred1)<<endl;
    cout<<cat::mean_squared_loss(y_true1, y_pred1)<<endl;
    
    vector<double> y_true2 = {1,1,1,0,0,0};
    vector<double> y_pred2 = {0.8,0.7,0.98,0.2,0.4,0.1};
    cout<<cat::log_loss(y_true2, y_pred2)<<endl;

    return 0;
}
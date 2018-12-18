/**
 * Author: xiaoran
 * Time: 2018-12-17
 */ 

#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    string filename = "../data/mytest.csv";
    vector<vector<string> > data = algo::csv2vector(filename);
	
	for(int k = 0; k < data.size(); k ++) {
		for(int i = 0; i < data[k].size(); i ++) {
			cout<<data[k][i]<<",";
		}
		cout<<endl;
	}

	vector<vector<double> > new_data = algo::str2float(data);
	for(int k = 0; k < new_data.size(); k ++) {
		for(int i = 0; i < new_data[k].size(); i ++) {
			cout<<new_data[k][i]<<",";
		}
		cout<<endl;
	}

	cout<<new_data.size()<<endl;

    return 0;
}

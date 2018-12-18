/**
 * Author: xiaoran
 * Time: 2018-12-18
 *
 */


#include "common.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	vector<double> a = {1,2,3,4};
	double b = 1;

	a = algo::add(a, b);

	for(int i = 0; i < a.size(); i++) {
		cout<<a[i]<<" ";
	}
	cout<<endl;
	return 0;
}

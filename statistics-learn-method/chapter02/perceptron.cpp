/**
 * Author: xiaoran
 * Time: 2018-12-15
 */

#include "../common/utils.h"
#include "../common/common.h"
#include "perceptron.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	// 读取数据
	string filename = "../data/train_binary.csv";
	vector<vector<string> > str_data = algo::csv2vector(filename);
	vector<vector<double> > data = algo::str2float(str_data);

	// 得到第一列作为y，labels
	vector<double> y_ = algo::get_column(data, 1);	
	vector<int> y = algo::float2int(y_);

	// remove label
	algo::remove_column(data, 1);
	
	// repalce 0, -1
	replace(y.begin(), y.end(), 0, -1);
	
	cout<<y.size()<<endl;
	cout<<data.size()<<endl;

	cat::Perceptron clf(100, 1.0, "l1", 0.001, 0.001, 50);
	
	algo::TT<double, int> tt = algo::train_test_split(data, y);
	
	clf.train(tt.train_datas, tt.train_labels);
	
	// 使用对偶方式训练
	// clf.train_v(tt.train_datas, tt.train_labels);

	clf.eval(tt.test_datas, tt.test_labels);

	return 0;
}

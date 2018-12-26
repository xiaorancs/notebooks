/**
 * Author: xiaoran
 * Time: 2018-12-26
 * distance functions 
 */ 

#ifndef STATISTICS_LEARN_METHOD_DISTANCE_H_
#define STATISTICS_LEARN_METHOD_DISTANCE_H_

#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>

namespace algo {
	
	/** 欧式距离 **/
	template<typename T>
	double euclidean_distance(std::vector<T> a, std::vector<T> b) {
		assert(a.size() == b.size());
		if(a.empty() || b.empty()) return 0.0;
		double ans = 0.0;
		for(int i = 0; i < a.size(); i++) {
			ans += (a[i] - b[i]) * (a[i] - b[i]);
		}
		return sqrt(ans);
	}
	
	/** 曼哈顿距离 **/
	template<typename T>
	double manhattan_distance(std::vector<T> a, std::vector<T> b) {
		assert(a.size() == b.size());
		if(a.empty() || b.empty()) return 0.0;
		double ans = 0.0;
		for(int i = 0; i < a.size(); i++) {
			ans += (a[i] - b[i]) > 0 ? (a[i] - b[i]) : (b[i] - a[i]);
		}
		return ans;
	}
	
	/** p=oo minkowski距离 **/
	template<typename T>
	double max_distance(std::vector<T> a, std::vector<T> b) {
		assert(a.size() == b.size());
		if(a.empty() || b.empty()) return 0.0;
		double ans = 0.0;
		for(int i = 0; i < a.size(); i++) {
 			double temp = (a[i] - b[i]) > 0 ? (a[i] - b[i]) : (b[i] - a[i]);
			if(ans < temp) ans = temp;
		}
		return ans;
	}

}; // algo


#endif // STATISTICS_LEARN_METHOD_DISTANCE_H_

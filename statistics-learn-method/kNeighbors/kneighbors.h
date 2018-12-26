/**
 * Author: xiaoran
 * Time: 2018-12-25
 * k neighbor includes kNeighborClassifier, kNeighborRegression
 */

#ifndef STATISTICS_LEARN_METHOD_NEIGHBORS_H_
#define STATISTICS_LEARN_METHOD_NEIGHBORS_H_

#include "../common/distance.h"
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stdio.h>
#include <assert.h>

namespace cat {

/**大根堆的比较方式 **/
struct cmp {
	template<typename T1, typename T2>
	bool operator() (T1 const& left, T2 const& right) {
		return left.second < right.second;
	}
};

template<typename T1=double, typename T2=int>
class KNeighbors {
public:
	KNeighbors(): n_neighbors(5), algorithm("auto"), p(2) {}
	KNeighbors(int _n_neighbors, std::string _algorithm, int _p):
	   n_neighbors(_n_neighbors), algorithm(_algorithm), p(_p) {
		assert(algorithm == "auto" || algorithm == "kd_tree");   		
		if(algorithm == "kd_tree") { // 构造KDTree
			
		}
	}
	
	/** 训练模型，填充数据 **/
	void train(std::vector<std::vector<T1> > X, std::vector<T2> y) {
		datas = X;
		labels = y;
	}
	
	/** get top k ， 使用大根堆**/
	std::vector<int> get_KNeighbors_by_auto(std::vector<std::vector<T1> > datas, std::vector<T1> target, int k, int p=2) {
		assert(p == 1 || p == 2);
		// 使用大根堆
		std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double> >, cmp> pq;	
		
		double dist = 0.0;
		for(int i = 0; i < datas.size(); i ++) {
			if(p == 2){
				dist = algo::euclidean_distance(datas[i], target);
			}
			else {
				dist = algo::manhattan_distance(datas[i], target);
			}
			if(pq.size() < k) {
				pq.push(std::make_pair(i, dist));
			}
			else {
				if(pq.top().second > dist) {
					pq.pop();
					pq.push(std::make_pair(i, dist));
				}
			}
		}
		std::vector<int> ans;
		while(!pq.empty()){
			ans.push_back(pq.top().first);
			pq.pop();
		}
		return ans;
	}

	/** get_KNeighbors **/
	std::vector<int> get_KNeighbors(std::vector<T1> target) {
		std::vector<int> ans;
		// 直接使用的方式
		if(algorithm == "auto") {
			ans = get_KNeighbors_by_auto(datas, target);
		}
		else { // kd tree
			
		}
		return ans;
	}

	/** 预测结果, 子类进行实现 **/
	virtual T2 predict(std::vector<T1> x) = 0;


private:
	int n_neighbors; // kNN 参数中的k值，默认: 5
	std::string algorithm; // 使用的构造算法，支持{"auto", "kd_tree"}
	int p; // 使用的minkowski距离， p代表使用的距离公式，默认是2，使用欧氏距离
	
	// 训练数据
	std::vector<std::vector<T1> > datas;
	std::vector<T2> labels; 
	
	// KDTree kdtree;


}; // kNeighbors

}; // cat


#endif // STATISTICS_LEARN_METHOD_NEIGHBORS_H_ 

/**
 * Author: xiaoran
 * Time: 2018-12-15
 */ 
#ifndef STATISTICS_LEARN_METHOD_PERCEPTRON_H_
#define STATISTICS_LEARN_METHOD_PERCEPTRON_H_

#include "../common/common.h"
#include "../common/utils.h"
#include "../chapter01/metrics.h"
#include <iostream>
#include <vector>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

namespace cat {

class Perceptron {
public:
    Perceptron():
        max_iter(1000), 
        eta(1.0),
        penalty("l2"),
        alpha(0.001),
        tol(0.0001),
        verbose(0),
        shuffle(true) { }
    Perceptron(int _max_iter, double _eta=1.0, std::string _penalty="l2", 
                double _alpha=0.001, double _tol=0.0001, int _verbose=0, bool _shuffle=true):
        max_iter(_max_iter), 
        eta(_eta),
        penalty(_penalty),
        alpha(_alpha),
        tol(_tol),
        verbose(_verbose),
        shuffle(_shuffle) { }

    /**训练模型，使用原始算法**/
    template<typename T>
    void train(std::vector<std::vector<T> > X, std::vector<int> y) {
        assert(X.size() == y.size());
        
		std::vector<T> w_u(X[0].size(), 0);
        double b_u = algo::random();
        // 使用随机函数重新赋值
        algo::normal_random(w_u);

        // 打乱数据
        if(shuffle == true) {
            algo::shuffle(X, y);
        }

        bool all_correct = false;
        int iter = 0;
        double pre_loss = 100.0, loss = 0.0;
        while(iter < max_iter && fabs(loss - pre_loss) >= tol) {
            pre_loss = loss;
            // 随机选择一个数据
            loss = 0.0;
			all_correct = true;
			
			for(int i = 0; i < X.size(); i++) {
				double temp = y[i] * (algo::dot_mult(X[i], w_u) + b);
				if(temp <= 0) { // 存在错误分类的点
                	loss -= temp;
                	// 更新参数
					if(penalty == "none") { // 不使用正则项
               	 		w_u = algo::add(w_u, algo::mul(X[i], eta * y[i]));
                		b_u = b_u + eta * y[i];
					}
					else if(penalty == "l2") {
						w_u = algo::sub(w_u, algo::mul(w_u, alpha));
						w_u = algo::add(w_u, algo::mul(X[i], eta * y[i]));
						b_u = b_u + eta * y[i];	
					}
					else if(penalty == "l1") {
						std::vector<double> _tw = algo::sign(w_u);
						w_u = algo::sub(w_u, algo::mul(_tw, alpha));
						w_u = algo::add(w_u, algo::mul(X[i], eta * y[i]));
						b_u = b_u + eta * y[i];	
					}
					else {
						printf("正则项参数penalty错误！仅仅支持:{none, l1, l2}\n");
						return;
					}
            		all_correct = false;
				}
			}
			
			// 所有都正确分类
			if(all_correct) {
				break;
			}

            iter ++;
            if(verbose > 0 && iter % verbose == 0) {
                printf("Iter %d, current avg loss: %.5lf. \n", iter, loss / y.size());
            }
        }
        w = w_u;
        b = b_u;
    }

    /**训练模型，使用对偶算法**/
    template<typename T>
    void train_v(std::vector<std::vector<T> > X, std::vector<int> y) {
 		std::vector<std::vector<T> > gram = algo::gram_mat(X);
		
		std::vector<T> a_u(X.size(), 0);
        double b_u = algo::random();
        // 使用随机函数重新赋值
        algo::normal_random(a_u);
		// 打乱数据
        if(shuffle == true) {
            algo::shuffle(X, y);
        }

        bool all_correct = false;
        int iter = 0;
        double pre_loss = 100.0, loss = 0.0;
        while(iter < max_iter && fabs(loss - pre_loss) >= tol) {
            pre_loss = loss;
            // 随机选择一个数据
            loss = 0.0;
			all_correct = true;
			
			for(int i = 0; i < X.size(); i++) {
				double temp = 0.0;
				
				for(int j = 0; j < X.size(); j++) {
					temp += y[j] * a_u[j] * gram[j][i];
				}
				temp += b;

				if(temp <= 0) { // 存在错误分类的点
                	loss -= temp;
                	// 更新参数
               	 	a_u[i] = a_u[i] + eta;
                	b_u = b_u + eta * y[i];
            		all_correct = false;
				}
			}
			
			// 所有都正确分类
			if(all_correct) {
				break;
			}

            iter ++;
            if(verbose > 0 && iter % verbose == 0) {
                printf("Iter %d, current avg loss: %.5lf. \n", iter, loss / y.size());
            }
        }
        w = a_u;
        b = b_u;
    }

    /**预测结果**/
    template<typename T>
    int predict(std::vector<T> x) {
        int target = (algo::dot_mult(w, x) + b) > 0 ? 1 : -1;
    	return target;
	}

    /**预测结果**/
    template<typename T>
    std::vector<int> predict(std::vector<std::vector<T> > X) {
        std::vector<int> targets;
		for(int i = 0; i < X.size(); i ++) {
            targets.push_back(predict(X[i]));
        }
		return targets;
    }

    /**验证模型**/
    template<typename T>
    double eval(std::vector<std::vector<T> > X, std::vector<int> y) {
		std::vector<int> pre_y = predict(X);
		double score = cat::accuracy_score(y, pre_y);
		std::cout<<score<<std::endl;
    	return score;
	}

	std::vector<double> get_weight() {
		return w;
	}

	double get_bais() {
		return b;
	}


private:
    std::vector<double> w; // 权重
    double b;   // 偏差

    int max_iter; // 最大迭代次数，当tol为空的时候，默认是1000，
    int n_iter; // 迭代次数，和tol，必须选择一个
    double eta; // 学习率, 默认是1.0
    std::string penalty; // 正则项,支持L1和L2，None
    double alpha; // 正则项的系数， 默认是0.001
    double tol; // 停止的阈值，|pre_loss - loss| < tol, default 1e-3
    int verbose; // 迭代显示次数， 默认是0，不进行显示
    bool shuffle; // 是否重新打乱数据，默认是重新打乱true

};

};

#endif // STATISTICS_LEARN_METHOD_PERCEPTRON_H_

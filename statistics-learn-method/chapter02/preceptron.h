/**
 * Author: xiaoran
 * Time: 2018-12-15
 */ 
#ifndef STATISTICS_LEARN_METHOD_PERCEPTRON_H_
#define STATISTICS_LEARN_METHOD_PERCEPTRON_H_

#include "../common.h"
#include "../chapter01/metrics.h"
#include <iostream>
#include <vector>
#include <assert.h>
#include <math.h>
#include <stdio.h>

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
    Perceptron(int _max_iter=1000, double _eta=1.0, std::string _penalty="l2", 
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
    void train(std::vector<std::vector<T> > &X, std::vector<int> &y) {
        assert(X.size() == Y.size());
        
        vector<T> w_u(Y.size(), 0);
        double b_w = algo::random();
        // 使用随机函数重新赋值
        algo::normal_random(w_u);

        // 打乱数据
        if(shuffle == true) {
            algo::shuffle(X, y);
        }

        bool all_correct = false;
        int iter = 0;
        double pre_loss = 100.0, loss = 0.0; 
        while(iter < max_iter && fabs(pre_loss - loss) < tol && all_correct) {
            pre_loss = loss;
            loss = 0.0;
            all_correct = true;
            for(int i = 0; i < X.size(); i ++) {
                double temp = y[i] * (algo::dot_mult(X[i], w_u) + b);
                if(temp <= 0) { // 存在错误分类的点
                    loss -= temp;
                    all_correct = false;
                    
                    // 更新参数
                    w_u = algo::add(w_u, algo::add(algo::mul(X[i], eta * y[i]), alpha));
                    b_u = b_u + eta * y[i];
                    break;
                }
            }
            iter ++;
            if(!verbose && iter % verbose == 0) {
                printf("Iter %d, current loss: %5.lf. \n", iter, loss);
            }
        }
        w = w_u;
        b = b_u;
    }

    /**训练模型，使用对偶算法**/
    template<typename T>
    void train_v(std::vector<std::vector<T> > &X, std::vector<int> &y) {
        
    }

    /**预测结果**/
    template<typename T>
    void predict(std::vector<T> x, int &target) {
        target = (algo::dot_mult(w, x) + b) > 0 ? 1 : -1;
    }

    /**预测结果**/
    template<typename T>
    void predict(std::vector<std::vector<T>> X, vector<int> &target) {
        for(int i = 0; i < X.size(); i ++) {
            predict(X[i], target[i]);
        }
    }

    /**验证模型**/
    template<typename T>
    void eval(std::vector<std::vector<T>> X, vector<int> y) {
        vector<int> pre_y;
        predict(X, pre_y);

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
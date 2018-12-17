/**
 * Author: xiaoran
 * Time: 2018-12-15
 * 
 */ 

#ifndef STATISTICS_LEARN_METHOD_COMMON_H_
#define STATISTICS_LEARN_METHOD_COMMON_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

namespace algo {

    // ans = a * c (矩阵相乘)
    template<typename T>
    void matrix_malt(const std::vertor<vector<T> > a, const std::vertor<vector<T> > b, const std::vertor<vector<T> > &ans) {

    }

    template<typename T>
    double dot_mult(const std::vector<T> a, const std::vector<T> b) {
        assert(!a.empty());
        assert(!b.empty());
        assert(a.size() == b.size());
        
        double sum = 0.0;
        for(int i = 0; i < a.size(); i ++) {
            sum += a[i] * b[i];
        }
        return sum;
    }

    // 随机初始化到0-1之间的函数
    template<typename T>
    void normal_random(std::vector<std::vector<T>> &a ) {
        for(int i = 0; i < a.size(); i ++) {
            normal_random(a[i]);
        }
    }
    
    template<typename T>
    void normal_random(std::vector<T> &a ) {
        for(int i = 0; i < a.size(); i++) {
            a[i] = random();
        }
    }

    inline double random() {
        srand((unsigned int)time(0));
        return 1.0 * rand() / RAND_MAX;
    }

    template<typename T1, typename T2=int>
    void shuffle(std::vector<std::vector<T1>> &X, std::vector<T2> &y) {
        assert(X.size() == y.size());
        srand(time(NULL));
        int j;
        for(int i = 0; i < X.size(); i++) {
            j = rand() % (i + 1);
            swap(X[i], X[j]);
            swap(y[i], y[j]);
        }
    }

    /**a = a + b**/
    template<typename T>
    vector<T> add(vector<T> &a, vector<T> b) {
        assert(a.size() == b.size());
        for(int i = 0; i < a.size(); i ++) {
            a[i] += b[i];
        }
        return a;
    }

    /**a = a + b**/
    template<typename T>
    vector<T> add(vector<T> &a, T b) {
        for(int i = 0; i < a.size(); i ++) {
            a[i] += b;
        }
        return a;
    }
    
    /**向量中每个元素对应取反 **/
    template<typename T>
    vector<T> negate(vector<T> &a) {
        for(int i = 0;i < a.size(); i ++) {
            a[i] = -a[i];   
        }
        return a;
    }

    /**a = a-b **/
    template<typename T>
    vector<T> sub(vector<T> &a, vector<T> b) {
        b = negate(b);
        rerturn add(a, b);
    }

    /**a = a-b **/
    template<typename T>
    vector<T> sub(vector<T> &a, T b) {
        b = -b;
        rerturn add(a, b);
    }

    /**a = a * b , 对应相乘，使用的是广播**/
    template<typename T>
    vector<T> mul(vector<T> &a, vector<T> b) {
        assert(a.size() == b.size());
        for(int i = 0; i < a.size(); i ++) {
            a[i] *= b[i];
        }
        return a;
    }

    /**a = a * b , 对应相乘，使用的是广播**/
    template<typename T>
    vector<T> mul(vector<T> &a, T b) {
        assert(a.size() == b.size());
        for(int i = 0; i < a.size(); i ++) {
            a[i] *= b;
        }
        return a;
    }

};

#endif // STATISTICS_LEARN_METHOD_COMMON_H_
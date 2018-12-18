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
	
	template<typename T1, typename T2>
	struct TT {
		std::vector<std::vector<T1> > train_datas;
		std::vector<std::vector<T1> > test_datas;
		std::vector<T2> train_labels;
		std::vector<T2> test_labels;
		TT() {}
		
		TT( std::vector<std::vector<T1> > _train_datas,
			std::vector<std::vector<T1> > _test_datas,
			std::vector<T2> _train_labels,
			std::vector<T2> _test_labels):
			train_datas(_train_datas),
			test_datas(_test_datas),
			train_labels(_train_labels),
			test_labels(_test_labels) {}
	};

    // ans = a * c (矩阵相乘)
    template<typename T>
    std::vector<std::vector<T> > matrix_mul(const std::vector<std::vector<T> > a, const std::vector<std::vector<T> > b) {
		int row_a = a.size();
		int col_a = a[0].size();
		int row_b = b.size();
		int col_b = b[0].size();
		assert(col_a == row_b);
		std::vector<std::vector<T> > ans(row_a, std::vector<T>(col_b, 0));

		for(int i = 0; i < row_a; i++) {
			for(int j = 0; j < col_b; j++) {
				double t = 0;
				for(int k = 0; k < col_a; k++) {
					ans[i][j] += a[i][k] * a[k][j];
				}
			}
		}
		return ans;
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

	// get gram matrix
    template<typename T>
    std::vector<std::vector<T> > gram_mat(const std::vector<std::vector<T> > a) {
		int row_a = a.size();
		int col_a = a[0].size();
		std::vector<std::vector<double> > ans(row_a, std::vector<T>(row_a, 0));

		for(int i = 0; i < row_a; i++) {
			for(int j = 0; j < row_a; j++) {
				ans[i][j] = dot_mult(a[i], a[j]);
			}
		}
		return ans;
    }



    // 随机初始化到0-1之间的函数
    template<typename T>
    void normal_random(std::vector<std::vector<T> > &a ) {
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
    void shuffle(std::vector<std::vector<T1> > &X, std::vector<T2> &y) {
        assert(X.size() == y.size());
        srand(time(NULL));
        int j;
        for(int i = 0; i < X.size(); i++) {
            j = rand() % (i + 1);
			std::swap(X[i], X[j]);
			std::swap(y[i], y[j]);
        }
    }

    /**a = a + b**/
    template<typename T>
    std::vector<T> add(std::vector<T> a, std::vector<T> b) {
        assert(a.size() == b.size());
		std::vector<T> ans;
        for(int i = 0; i < a.size(); i ++) {
            ans.push_back(a[i] + b[i]);
        }
        return ans;
    }

    /**a = a + b**/
    template<typename T>
    std::vector<T> add(std::vector<T> a, T b) {
		std::vector<T> ans;
        for(int i = 0; i < a.size(); i ++) {
            ans.push_back(a[i] + b);
        }
        return ans;
    }
    
    /**向量中每个元素对应取反 **/
    template<typename T>
    std::vector<T> negate(std::vector<T> a) {
		std::vector<T> ans;
        for(int i = 0;i < a.size(); i ++) {
            ans.push_back(-a[i]);   
        }
        return ans;
    }

    /**a = a-b **/
    template<typename T>
    std::vector<T> sub(std::vector<T> a, std::vector<T> b) {
		std::vector<T> bb = negate(b);
        return add(a, bb);
    }

    /**a = a-b **/
    template<typename T>
    std::vector<T> sub(std::vector<T> a, T b) {
        b = -b;
        return add(a, b);
    }

    /**a = a * b , 对应相乘，使用的是广播**/
    template<typename T>
    std::vector<T> mul(std::vector<T> a, std::vector<T> b) {
        assert(a.size() == b.size());
		std::vector<T> ans;
        for(int i = 0; i < a.size(); i ++) {
            ans.push_back(a[i] * b[i]);
        }
        return ans;
    }

    /**a = a * b , 对应相乘，使用的是广播**/
    template<typename T>
    std::vector<T> mul(std::vector<T> a, T b) {
       	std::vector<T> ans;
        for(int i = 0; i < a.size(); i ++) {
            ans.push_back(a[i] * b);
        }
        return ans;
    }

	// 划分数据集
	template<typename T1,typename T2>
	TT<T1, T2> train_test_split(std::vector<std::vector<T1> > data, std::vector<T2> y, double test_size=0.2) {
		int t = (int) data.size() * test_size;
		std::vector<std::vector<T1> > train_datas(data.begin(), data.begin() + t);
		std::vector<std::vector<T1> > test_datas(data.begin() + t, data.end());
		
		std::vector<T2> train_labels(y.begin(), y.begin() + t);
		std::vector<T2> test_labels(y.begin() + t, y.end());

		return TT<T1, T2>(train_datas, test_datas, train_labels, test_labels);
	}

};

#endif // STATISTICS_LEARN_METHOD_COMMON_H_

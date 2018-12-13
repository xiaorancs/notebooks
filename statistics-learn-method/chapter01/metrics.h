/**
 * Author: xiaoran
 * Time: 2018-12-13
 */ 

#ifndef STATISTICS_LEARN_METHOD_METRICS_H_
#define STATISTICS_LEARN_METHOD_METRICS_H_


#include <vector>
#include <assert.h>
#include <math.h>

namespace StatsMethod {

    /** 0-1损失函数 **/
    template<typename T>
    double zero_one_loss(const std::vector<T> y_true, const std::vector<T> y_pred) {
        double source = 0.0;
        assert(!y_true.empty());
        assert(!y_pred.empty());
        assert(y_true.size() == y_pred.size());

        for(int i = 0; i < y_true.size(); i++) {
            if(y_true[i] != y_pred[i]) {
                source += 1;
            }
        }
        source = source / y_true.size();
        return source;
    }

    /** acc正确率函数 **/
    template<typename T>
    double accuracy_score(const std::vector<T> y_true, const std::vector<T> y_pred) {
        return 1 - zero_one_loss(y_true, y_pred);
    }

    /** 平均平方损失 **/
    template<typename T>
    double mean_squared_loss(const std::vector<T> y_true, const std::vector<T> y_pred) {
        double source = 0.0;
        assert(!y_true.empty());
        assert(!y_pred.empty());
        assert(y_true.size() == y_pred.size());
        for(int i = 0; i < y_true.size(); i++) {
            source += (y_true[i] - y_pred[i]) * (y_true[i] - y_pred[i]);
        }
        source = source / y_true.size();
        return source;
    }

    /** 平均绝对值损失 **/
    template<typename T>
    double mean_absolute_loss(const std::vector<T> y_true, const std::vector<T> y_pred) {
        double source = 0.0;
        assert(!y_true.empty());
        assert(!y_pred.empty());
        assert(y_true.size() == y_pred.size());
        for(int i = 0; i < y_true.size(); i++) {
            source += fabs(y_true[i] - y_pred[i]);
        }
        source = source / y_true.size();        
        return source;
    }

    /** 对数损失 **/
    template<typename T>
    double log_loss(const std::vector<T> y_true, const std::vector<T> y_pred) {
        double source = 0.0;
        assert(!y_true.empty());
        assert(!y_pred.empty());
        assert(y_true.size() == y_pred.size());
        for(int i = 0; i < y_true.size(); i++) {
            assert(y_pred[i] <= 1);
            assert(y_pred[i] >= 0);
            source -= log(y_pred[i]);
        }
        source = source / y_true.size();        
        return source;
    }

}; 

#endif // STATISTICS_LEARN_METHOD_METRICS_H_
# _*_coding: utf-8_*_
# Author: xiaoran
# Time 2018-12-15

import pandas as pd
import numpy as np
import time

from sklearn.cross_validation import train_test_split
from sklearn.metrics import accuracy_score


class Perceptron(object):

    def __init__(self, max_iter=1000, eta=1.0, penalty="l2", alpha=0.001, tol=0.0001, verbose=0, shuffle=True):
        '''
        param:
            max_iter: int, 最大的迭代次数, 默认1000
            eta: float, 学习率，默认1.0
            penalty: str, 正则项参数, 默认l2, {none, l1, l2}
            alpha: float, 正则项系数， 默认0.001
            tol: float, 损失停止阈值，pre_loss - loss < tol, stoped. 默认0.0001
            verbose: int, 迭代显示的此时，默认是0，不显示
            shuffle: bool, 是否打乱数据，默认打乱True
        '''
        self.max_iter = max_iter
        self.eta = eta
        self.penalty = penalty
        self.alpha = alpha
        self.tol = tol
        self.verbose = verbose
        self.shuffle = shuffle
        self.w = None
        self.b = None
    
    def fit(self, X, y):
        """
        param:
        X: narray, [n_sample x m_features], numpy 数组
        y: narray, [n_sample x 1], 和X一一对应
        """
        iter = 0
        all_correct = False
        pre_loss = 100.0
        loss = 0.0
        size = len(X)
        self.w = np.array([0] * len(X[0]))
        self.b = 0.0
        while iter < self.max_iter and np.abs(loss - pre_loss) >= self.tol:
            pre_loss = loss
            all_correct = True
            for i in range(size):
                temp = (np.sum(X[i] * self.w) +self.b) * y[i]
                if temp <= 0: # 是误分类的点
                    loss -= temp
                    if self.penalty == "none":
                        self.w = self.w + self.w * X[i] * y[i] * self.eta
                        self.b = self.b + self.eta * y[i]
                    elif self.penalty == "l2":
                        self.w = self.w - self.alpha * self.w
                        self.w = self.w + self.w * X[i] * y[i] * self.eta
                        self.b = self.b + self.eta * y[i]
                    elif self.penalty == "l1":
                        w_u = self.w.copy()
                        w_u[w_u > 0] = 1
                        w_u[w_u < 0] = -1
                        self.w = self.w + self.alpha * w_u
                        self.w = self.w + self.w * X[i] * y[i] * self.eta
                        self.b = self.b + self.eta * y[i]
                    else:
                        print("penalty参数错误,仅仅可以使用[none, l2, l1]")
                    all_correct = False
            if all_correct: # 所有正确分类
                break
            iter += 1
            if self.verbose > 0 and iter % self.verbose == 0:
                print("Iter %d, current avg loss: %.5lf", iter, loss / size)

    def predict_(self, x):
        """
        param:
        x: [n_feature]，一个测试样例
        return: 1 or -1
        """
        tmp = np.sum(self.w * x) + self.b
        return 1 if tmp > 0 else -1

    def predict(self, X):
        """
        param:
        X: narray, [n_sample x m_features], numpy 数组
        return y: list, 包含-1 or 1 和X一一对应
        """
        pre_y = []
        for x in X:
            pre_y.append(self.predict_(x))
        return np.array(pre_y)
        
    def score(self, X, y):  
        """
        param:
        X: narray, [n_sample x m_features], numpy 数组
        y: narray, [n_sample x 1], 和X一一对应
        return: double, 测试集合上的得分
        """
        pre_y = self.predict(X)
        res = np.sum(pre_y == y)
        return 1.0 * res / len(X)
    
if __name__ == "__main__":
    data = pd.read_csv("../data/train_binary.csv")
    labels = data['label']
    data = data[data.columns[1:]]
    data = data.values
    labels = labels.values
    train_features, test_features, train_labels, test_labels = train_test_split(
        data, labels, test_size=0.2)
    
    print(len(data))
    clf = Perceptron(max_iter=1000,verbose=20,penalty='none')
    clf.fit(train_features, train_labels)
    print(clf.score(test_features, test_labels))
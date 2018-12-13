# _*_coding:utf-8_*_
# Author: xiaoran
# Time: 2018-12-13

import numpy as np

def zero_one_loss(y_true, y_pred):
    '''
    param:
    y_true: narray or list
    y_pred: narray or list
    return: double 
    '''
    y_true = np.array(y_true)        
    y_pred = np.array(y_pred)        
    return 1.0 * (len(y_true) - np.sum(y_true == y_pred)) / len(y_true)

def accuracy_score(y_true, y_pred):
    '''
    param:
    y_true: narray or list
    y_pred: narray or list
    return: double 
    '''
    y_true = np.array(y_true)        
    y_pred = np.array(y_pred)        
    return 1.0 * np.sum(y_true == y_pred) / len(y_true)

def mean_absolute_loss(y_true, y_pred):
    '''
    param:
    y_true: narray or list
    y_pred: narray or list
    return: double 
    '''
    y_true = np.array(y_true)        
    y_pred = np.array(y_pred)
    return 1.0 * np.sum(np.abs(y_true - y_pred)) / len(y_pred)        
    
def mean_squared_loss(y_true, y_pred):
    '''
    param:
    y_true: narray or list
    y_pred: narray or list
    return: double 
    '''
    y_true = np.array(y_true)        
    y_pred = np.array(y_pred)
    return 1.0 * np.sum((y_true - y_pred)**2) / len(y_pred)        
    

def log_loss(y_true, y_pred):
    '''
    param:
    y_true: narray or list
    y_pred: narray or list
    return: double 
    '''
    y_true = np.array(y_true)        
    y_pred = np.array(y_pred)
    
    return np.sum(-np.log(y_pred)) / len(y_pred)
    

if __name__ == "__main__":
    y_true = [1,1,1,0,0,0]
    y_pred = [1,0,1,0,0,1]

    print(zero_one_loss(y_true, y_pred))
    print(accuracy_score(y_true, y_pred))

    y_true1 = [1.1,1.2,1.3,2,3,4]
    y_pred1 = [1,0,1,2,3,4]

    print(mean_absolute_loss(y_true1, y_pred1))
    print(mean_squared_loss(y_true1, y_pred1))
    
    y_true2 = [1,1,1,0,0,0]
    y_pred2 = [0.8,0.7,0.98,0.2,0.4,0.1]
    print(log_loss(y_true2, y_pred2))


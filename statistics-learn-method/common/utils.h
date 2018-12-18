/**
 * Author: xiaoran
 * Time: 2018-12-17
 * 
 */ 

#ifndef STATISTICS_LEARN_METHOD_COMMON_UTILS_H_
#define STATISTICS_LEARN_METHOD_COMMON_UTILS_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>

#include <boost/format.hpp>   
#include <boost/tokenizer.hpp>  
#include <boost/algorithm/string.hpp>

namespace algo {

    /** 读取csv到str， 默认忽略csv的第一行头**/
    std::vector<std::vector<std::string> > csv2vector(std::string filename, bool header=true) {
		std::ifstream fin(filename, std::ios::in);
        std::vector<std::vector<std::string> > data;
        std::string line;

        // 跳过第一行
        if(header) getline(fin, line);

        while(getline(fin, line)) {
            std::vector<std::string> tmp;
            boost::split(tmp, line, boost::is_any_of(","));
            data.push_back(tmp);
        }
        
        if(fin) fin.close();
        return data;
    }
    
    template<typename T>
    void vector2csv(std::string filename, std::vector<std::vector<T> > data) {

    }

    /** 转化str到 double, 空值用0.0填充 **/
   	std::vector<std::vector<double> > str2float(std::vector<std::vector<std::string> > data, double fillna=0.0) {
		std::vector<std::vector<double> > new_data;
		for(int i = 0; i < data.size(); i++) {
			std::vector<double> tmp;
			for(int j = 0; j < data[i].size(); j++) {
				if(data[i][j] == "") {
					tmp.push_back(fillna);
				}
				else {
					tmp.push_back(std::stod(data[i][j]));
				}
			}
			new_data.push_back(tmp);
		}
		return new_data;
    }

	/** 得到第k列的数据 **/
	template<typename T>
	std::vector<T> get_column(std::vector<std::vector<T> > data, int column) {
		std::vector<T> result;
		for(int i = 0; i < data.size(); i ++) {
			result.push_back(data[i][column-1]);
		}
		return result;
	}
	
	/** remove 指定的列数据 **/
	template<typename T>
	std::vector<std::vector<T> > remove_column(std::vector<std::vector<T> > &data, int column) {
		std::vector<std::vector<T> > new_data;
		for(int i = 0; i < data.size(); i++) {
			std::vector<T> tmp;
			for(int j = 0; j < data[i].size(); j++) {
				if(j == column - 1) continue;
				tmp.push_back(data[i][j]);
			}
			data[i] = tmp;
			new_data.push_back(tmp);
		}
		return new_data;
	}

	/**double 2 int**/
	std::vector<int> float2int(std::vector<double> data) {
		std::vector<int> new_data;
		for(int i = 0; i < data.size(); i ++) {
			new_data.push_back((int) data[i]);
		}
		return  new_data;
	}

	/**sign(vector)**/
	std::vector<double> sign(std::vector<double> w) {
		std::vector<double> w_;
		for(int i = 0; i < w.size(); i++) {
			if(w[i] < 0) {
				w_.push_back(-1);
			}
			else if(w[i] > 0) {
				w_.push_back(1);
			}
			else {
				w_.push_back(0);
			}	
		}
		return w_;
	}

};


#endif // STATISTICS_LEARN_METHOD_COMMON_UTILS_H_

#pragma once

#include<boost/python/list.hpp>
#include<boost/python/extract.hpp>
#include<vector>
#include<string>

#include "consts.h"

using namespace std;

template<class type>
std::vector<type>  from_python_list(boost::python::list list) {
	int len = boost::python::len(list);
	std::vector<type> cats(len);
	for (int i = 0; i < len; ++i) {
		cats[i] = boost::python::extract<type>(list[i]);
	}
	return cats;
}

//vector<char*> from_python_list(boost::python::list list) {
//	int len = boost::python::len(list);
//	std::vector<char*> cats(len);
//	for (int i = 0; i < len; ++i) {
//		cats[i] = boost::python::extract<char*>(list[i]);
//	}
//	return cats;
//}

template<class type>
boost::python::list to_python_list(std::vector<type> vec) {
	boost::python::list list;
	for (auto& v : vec)
		list.append(v)
	return list;
}

template<int SIZE>
class char_array {
public:
	char_array() :data_(new char[SIZE]) {
		memset(data_, 0, SIZE);
	}
	string string() {
		return std::string(data_);
	}
	operator char* () {
		return data_;
	}
	~char_array() {delete data_; }
	char* data_;
};

typedef char_array<ERR_SIZE> tdx_error;
typedef char_array<RESULT_SIZE> tdx_data;

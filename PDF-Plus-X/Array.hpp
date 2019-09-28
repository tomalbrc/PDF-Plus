//
//  Array.hpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 28.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Array_hpp
#define Array_hpp

#include <cstdio>
#include <vector>

template <class T>
class Array {
public:
	Array() = default;
	Array(const std::vector<T>& data) : _data{data} {}
	Array(std::vector<T>&& data) : _data{std::move(data)} {}
	
	void append(const T& item) {
		_data.emplace_back(item);
	}
	
	void remove(const T& item) {
		_data.erase(std::remove(_data.begin(), _data.end(), item), _data.end());
	}
	
	auto size() const {
		return _data.size();
	}
	
	auto empty() const {
		return _data.empty();
	}
	
	friend std::ostream& operator<<(std::ostream& out, const Array<T>& array) {
		out << '[';
		
		for (const auto& item: array._data)
			out << item << ' ';
		
		out << ']';
	}
	
private:
	std::vector<T> _data;
};

#endif /* Array_hpp */

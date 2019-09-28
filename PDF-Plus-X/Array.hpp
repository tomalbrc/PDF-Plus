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
#include <iostream>

template <class... Ts>
class Array {
public:
	using Value_t = std::variant<Ts...>;
	
	Array() = default;
	Array(const std::vector<Value_t>& data) : _data{data} {}
	Array(std::vector<Value_t>&& data) : _data{std::move(data)} {}
	
	void append(const Value_t& item) {
		_data.emplace_back(item);
	}
	
	void remove(const Value_t& item) {
		_data.erase(std::remove(_data.begin(), _data.end(), item), _data.end());
	}
	
	auto size() const {
		return _data.size();
	}
	
	auto empty() const {
		return _data.empty();
	}
	
	auto& at(const std::size_t& idx) const {
		return _data.at(idx);
	}
	
	friend std::ostream& operator<<(std::ostream& out, const Array<Ts...>& array) {
		out << '[';
		
		if (!array._data.empty()) {
			for (auto it = array._data.begin(); it != array._data.end(); it++) {
				auto& val = *it;
		
				auto cb = [&](auto& item){
					out << item << (it==array._data.end()-1 ? "" :" ");
				};
				std::visit(cb, val);
			}
		}
		
		out << ']';
		
		return out;
	}
	
private:
	std::vector<Value_t> _data;
};

#endif /* Array_hpp */

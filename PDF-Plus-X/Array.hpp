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
#include "Util.h"

namespace PDF_Plus {
	/**
	
	 */
	template <class... Ts>
	class Array {
	public:
		using Value_t = std::variant<Ts...>;
	
		Array() = default;
	
		/**
	
		 */
		Array(Ts... args) : Array{args...} {}
		
		/**
		 
		 */
		Array(const std::initializer_list<Value_t>& data) : _data{data} {}
		Array(std::initializer_list<Value_t>&& data) : _data{std::move(data)} {}
		
		/**
		 Appends item at (array.size())
		 */
		auto append(const Value_t& item) {
			return _data.emplace_back(item);
		}
		
		/**
		 Insert item at index
		 */
		auto insert(const Value_t& item, const std::size_t& idx = 0) {
			return _data.insert(_data.begin() + idx, item);
		}
		
		/**
		 Remove item from Array
		 */
		void remove(const Value_t& item) {
			_data.erase(std::remove(_data.begin(), _data.end(), item), _data.end());
		}
	
		/**
		 Array size
		 */
		auto size() const {
			return _data.size();
		}
	
		/**
		 Array empty
		 */
		auto empty() const {
			return _data.empty();
		}
		
		/**
		 Set value to item. Can be of the ones specified in Ts
		 */
		Value_t& set(const std::size_t& idx) {
			return _data.at(idx);
		}
		
		/**
		 Will throw if template parameter Get_t
		 does not match with the type of the item at idx
		 */
		template <class Get_t>
		Get_t& get(const std::size_t& idx) {
			static_assert(VariantHelper::isVariantMember<Get_t, 	std::variant<Ts...>>::value, "type not in list");
			return std::get<Get_t>(_data.at(idx));
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
	
}

#endif /* Array_hpp */

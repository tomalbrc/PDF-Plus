//
//  Object.hpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 22.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <cstdio>
#include <sstream>
#include <string>
#include <map>
#include <variant>

namespace PDF_Plus {
	/**
	Dict
	*/
	template <class... Value_ts>
	class Dictionary {
	public:
		using Key_t = std::string;
		using Value_t = std::variant<Value_ts...>;
		
		/**
		 Braces operator, for easy manipulation of entries,
		 returns non-const ref to T for given key.
		 Example:
		 @codeline dict[TypeKey] = "/Page";
		 */
		Value_t& operator[](const Key_t& key)
		{
			return _props[key];
		}
		
		const Value_t& operator[](const Key_t& key) const
		{
			return _props.at(key);
		}
		
		/**
		 Writes the key-value pairs to out.
		 E.g.:
		 @codeline <</Type /Page /Contents 4 0 R>>
		 */
		std::ostream& write(std::ostream& out) const
		{
			std::string res;
			for (const auto& kvPair: _props) {
				auto& val = kvPair.second;
				std::ostringstream ss;
				
				auto cb = [&ss](auto& t) {
					ss << t;
				};
				std::visit(cb, val);
				
				res += "/" + kvPair.first + " " + ss.str() + " ";
			}
			
			if (!res.empty() && res.back() == ' ')
				res.pop_back(); // remove last char if space
			
			out << "<<" << res << ">>";
			
			return out;
		}
		
		/**
		 
		 */
		friend std::ostream& operator<<(std::ostream& out, const Dictionary& t)
		{
			return t.write(out);
		}
		
	private:
		std::map<Key_t, Value_t> _props;
	};
}

#endif /* Object_hpp */

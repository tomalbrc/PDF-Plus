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

namespace PDF_Plus {
	namespace Key {
		// TODO: Add all possible keys?
		const std::string TypeKey = "Type";
		const std::string LengthKey = "Length";
		const std::string FontKey = "Font";
	}
	
	template <class T>
	class Dict {
	public:
		using PropertyKey_t = std::string;
		
		/**
		 Braces operator, for easy manipulation of entries,
		 returns non-const ref to T for given key.
		 Example:
		 @codeline dict[TypeKey] = "/Page";
		 */
		T& operator[](const std::string& key)
		{
			return _props[key];
		}
		
		/**
		 Writes the key-value pairs to out.
		 E.g.:
		 @codeline <</Type /Page /Contents 4 0 R>>
		 */
		void write(std::ostream& out) const
		{
			std::string res;
			for (const auto& kvPair: _props) {
				res += "/" + kvPair.first + " " + kvPair.second + " ";
			}
			
			if (!res.empty() && res.back() == ' ')
				res.pop_back(); // remove last char if space
			
			out << "<<" << res << ">>";
		}
		
	private:
		using PropertyMap_t = std::map<PropertyKey_t, T>;
		
		PropertyMap_t _props;
	};
}

#endif /* Object_hpp */

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

template <class T>
class Dict {
public:
	using PropertyKey = std::string;
	
	T& operator[](const std::string& key)
	{
		return _props[key];
	}
	
	friend std::ostream& operator<<(std::ostream& out, const Dict& d)
	{
		const auto NL = '\n';
		for (const auto& kvPair: d._props) {
			out << "/" << kvPair.first << " " << kvPair.second << NL;
		}
		return out;
	}
	
private:
	using Properties = std::map<PropertyKey, T>;
	
	Properties _props;
};

#endif /* Object_hpp */

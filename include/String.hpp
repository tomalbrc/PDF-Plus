//
//  String.hpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 28.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef String_hpp
#define String_hpp

#include <stdio.h>

#include <cstdio>
#include <string>
#include <regex>
#include <iostream>

/**
 
 */
class String {
public:
	/**
	 
	 */
	String() = default;
	
	/**
	 
	 */
	String(const std::string& data) : _data{data} {}
	
	/**
	 
	 */
	String(std::string&& data) : _data{std::move(data)} {}
	
	auto operator==(const String& rhs) {
		return rhs._data == _data;
	}
	
	/**
	 
	 */
	friend std::ostream& operator<<(std::ostream& out, const String& str) {
		return out << '(' << str.escape(str._data) << ')';
	}
	
private:
	std::string _data;
	
	///
	std::string escape(const std::string& text) const
	{
		auto cpy = text;
		cpy = std::regex_replace(cpy, std::regex(R"(\\)"), R"(\\)");
		cpy = std::regex_replace(cpy, std::regex(R"(\()"), R"(\()");
		return std::regex_replace(cpy, std::regex(R"(\))"), R"(\))");
	}
};

#endif /* String_hpp */

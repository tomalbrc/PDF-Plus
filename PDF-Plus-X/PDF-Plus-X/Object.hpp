//
//  Object.hpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 23.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef XObject_hpp
#define XObject_hpp

#include <cstdio>
#include <string>
#include <sstream>
#include "Dict.hpp"

#define CREATE_FUNC(x) static std::shared_ptr<x> create(const Document* parent) \
{\
	auto v = std::make_shared<x>(); \
	parent->addObject(v);\
	return v;\
}

class Document;

class Object : std::enable_shared_from_this<Object> {
public:
	using Type = std::string;
	using Identifier = uint64_t;
	
	Object(const Document* parent, const Type& type);
	
	std::string& operator[](std::string key)
	{
		return _dict[key];
	}
	
	friend std::ostream& operator<<(std::ostream& out, const Object& obj)
	{
		obj.writeBegin(out);
		out << obj._dict;
		obj.writeEnd(out);
		
		return out;
	}
	
	std::size_t size() const
	{
		std::stringstream s;
		s << (*this);
		return s.str().size();
	}
	
	void setIdentifier(const Identifier& id)
	{
		_id = id;
	}
	
	const Identifier& identifier() const
	{
		return _id;
	}
	
	static std::string Ref(Object *o){
		return std::to_string(o->identifier()) + " 0 R";
	}
	
protected:
	const std::string NL = "\n";
	Identifier _id = 0;
	Type _type;
	Dict<std::string> _dict;
	
	void writeBegin(std::ostream& out) const
	{
		out << _id << " 0 obj" << NL;
		out << "<< /Type /" << _type << NL;
	}
	void writeEnd(std::ostream& out) const
	{
		out << ">>" << NL;
		out << "endobj" << NL;
	}
	
};

#endif /* XObject_hpp */

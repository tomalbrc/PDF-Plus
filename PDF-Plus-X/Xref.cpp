//
//  Xref.cpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 28.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include "Xref.hpp"
#include "Object.hpp"

namespace PDF_Plus {

	void Xref::add(Object* obj)
	{
		_objs.emplace_back(obj);
		obj->objectNumber(_objs.size());
	}
	
	/**
	
	*/
	void Xref::remove(Object* obj)
	{
		_objs.erase(std::remove(_objs.begin(), _objs.end(), obj), _objs.end());
	}
	
	/**
	
	*/
	void Xref::write(std::ostream& out, std::size_t headerOffset, std::string objref) const
	{
		std::stringstream ss;
		
		out << "xref" << '\n';
		out << "0 " << _objs.size()+1 << '\n';
		out << "0000000000 " << std::pow(2,16)-1 << " f" << '\n';
		
		std::size_t off = 0;
		for (auto& o: _objs)
		{
			out << std::setw(10) << std::setfill('0') << off+headerOffset << " 00000 n" << '\n';
			off += o->size();
		}
		
		out << "trailer <</Size " << _objs.size()+1 << " /Root 1 0 R /Info ";
		out << objref << ">>" << '\n';
		out << "startxref" << '\n';
		out << off + headerOffset << '\n'; // Directly After Header
	}
}

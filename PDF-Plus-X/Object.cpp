//
//  Object.cpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 24.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include "Object.hpp"
#include "Document.hpp"

namespace PDF_Plus {

	Object::Object(const Document* parent, const Type& type)
	{
		if (!type.empty())
			_dict[Key::TypeKey] = std::string{"/"} + type;
		
        if (parent) {
            _xref = parent->xref();
            _xref.lock()->add(this);
        }
	}

	Object::~Object()
	{
		if (auto x = _xref.lock())
            x->remove(this);
	}

	std::string& Object::operator[](std::string key)
	{
		return _dict[key];
	}

	void Object::write(std::ostream& out)
	{
		out << _number << " 0 obj";
		_dict.write(out);
		writeEnd(out);
	}

	std::size_t Object::size() const
	{
		std::stringstream s;
        auto o = *this;
        o.write(s);
		return s.str().length();
	}

	std::string Object::Ref(Object *o){
		return std::to_string(o->objectNumber()) + " 0 R";
	}

    /// MARK: Private

	/// Write object begin
	/// @codeline '1 0 obj'
	void Object::writeBegin(std::ostream& out) const
	{
		// Object number -space- Object Generation
		out << _number << " 0 obj";
	}
	
	/// Write object end,
	/// @codeline 'endobj'
	void Object::writeEnd(std::ostream& out) const
	{
		out << "endobj" << NL;
	}

	void Object::objectNumber(const uint64_t& num)
    {
		_number = num;
	}
	
	const uint64_t& Object::objectNumber() const
    {
		return _number;
	}

    void Object::generationNumber(const uint64_t& gen)
    {
        _gen = gen;
    }
    
    const uint64_t& Object::generationNumber() const
    {
        return _gen;
    }
}

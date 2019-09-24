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
		_type = type;
		_parent = parent;
		_parent->addObject(this);
	}

	Object::~Object()
	{
		_parent->removeObject(this);
	}

	std::string& Object::operator[](std::string key)
	{
		return _dict[key];
	}

	void Object::write(std::ostream& out) const
	{
		writeBegin(out);
		_dict.write(out);
		writeEnd(out);
	}

	std::size_t Object::size() const
	{
		std::stringstream s;
		write(s);
		return s.str().size();
	}

	std::string Object::Ref(Object *o){
		return std::to_string(o->identifier()) + " 0 R";
	}

	/// MARK: Private

	// Write object begin, '1 0 obj <<'
	void Object::writeBegin(std::ostream& out) const
	{
		out << _id << " 0 obj";
		out << "<<";
		if (!_type.empty())
			// Only add Type info if the Type is set!
			out << "/Type /" << _type << ' ';
	}
	
	// Write object begin, '>> endobj'
	void Object::writeEnd(std::ostream& out) const
	{
		out << ">>" << NL;
		out << "endobj" << NL;
	}
	
	void Object::setIdentifier(const Identifier& id)
	{
		_id = id;
	}
	
	const Object::Identifier& Object::identifier() const
	{
		return _id;
	}
}

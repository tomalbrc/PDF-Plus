//
//  Object.cpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 24.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include "Object.hpp"
#include "Document.hpp"

Object::Object(const Document* parent, const Type& type)
{
    auto wptr = std::shared_ptr<Object>(this, [](Object*){});
	
	_type = type;
	parent->addObject(wptr);
}

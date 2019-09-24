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

namespace PDF_Plus {
	class Document;

	class Object {
	public:
		using Type = std::string;
		using Identifier = uint64_t;
		
		/**
		 
		 */
		Object(const Document* parent, const Type& type = {});
		
		/**
		 
		 */
		virtual ~Object();
		
		/**
		 
		 */
		std::string& operator[](std::string key);
		
		/**
		 
		 */
		virtual void write(std::ostream& out) const;
		
		/**
		 
		 */
		std::size_t size() const;
		
		/**
		 
		 */
		static std::string Ref(Object *o);
		
	protected:
		const char NL = '\n';
		
		Identifier _id = 0;
		Type _type;
		Dict<std::string> _dict;
		const Document* _parent = nullptr; // FIXME: Const-correct..?
		
		/**
		 Write object begin, '1 0 obj <<'
		 */
		void writeBegin(std::ostream& out) const;
		
		/**
		 Write object begin, '>> endobj'
		 */
		void writeEnd(std::ostream& out) const;
		
		
		friend class Document;
		/**
		 * Change Object id, only call this from Document
		 */
		void setIdentifier(const Identifier& id);
		
		/**
		 * Current Object id inside the document
		 */
		const Identifier& identifier() const;
	};
}

#endif /* XObject_hpp */

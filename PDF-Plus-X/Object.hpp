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
#include "Dictionary.hpp"
#include "Xref.hpp"

namespace PDF_Plus {
	class Document;

	class Object {
	public:
		using Type = std::string;
		
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
		virtual void write(std::ostream& out);
		
		/**
		 
		 */
		virtual std::size_t size() const;
		
		/**
		 
		 */
		static std::string Ref(Object *o);
		
	protected:
		const char NL = '\n';
		
		uint64_t _number = 0;
        uint64_t _gen = 0;
		
		Type _type;
		Dictionary<std::string> _dict;
		std::weak_ptr<Xref> _xref;
		
		/**
		 Write object begin, '1 0 obj\n'
		 */
		void writeBegin(std::ostream& out) const;
		
		/**
		 Write object begin, 'endobj\n'
		 */
		void writeEnd(std::ostream& out) const;
		
		
		
		friend class Xref;
		/**
		 Change Object id, only call this from Document
		 */
		void objectNumber(const uint64_t& id);
		
		/**
		 Current Object id inside the document
		 */
		const uint64_t& objectNumber() const;
        
        /**
         Object generation number
         */
        void generationNumber(const uint64_t& gen);
        
        /**
         Object generation number
         */
        const uint64_t& generationNumber() const;
	};
}

#endif /* XObject_hpp */

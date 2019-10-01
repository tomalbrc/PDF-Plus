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
#include <variant>

#include "String.hpp"
#include "Array.hpp"
#include "Dictionary.hpp"
#include "Xref.hpp"
#include "Key.h"

namespace PDF_Plus {
	using MultiVariantArray = Array<int, uint64_t, ObjectRef, std::string, String, float>;
	using MultiVariantDict = Dictionary<int, uint64_t, ObjectRef, std::string, String, float, MultiVariantArray>;
	
	/**
	
	*/
	class Object {
	public:
		/**
		 
		 */
		Object() = default;
		
		/**
		 
		 */
		Object(const std::weak_ptr<Xref>& parent) {
			if (auto p = parent.lock()) {
				_xref = parent;
				p->add(this);
			}
		}
		
		/**
		 
		 */
		virtual ~Object() {
			if (auto x = _xref.lock()) {
				x->remove(this);
			}
		}
		
		/**
		 
		 */
		MultiVariantDict::Value_t& operator[](const std::string& key) {
			return _dict[key];
		}
		
		/**
		 
		 */
		virtual std::ostream& write(std::ostream& out) {
			writeBegin(out);
			_dict.write(out);
			writeEnd(out);
			
			return out;
		}
		/**
		 
		 */
		virtual std::size_t size() const {
			std::ostringstream s;
			auto o = *this;
			o.write(s);
			return s.str().length();
		}
		
		/**
		 Current Object id inside the document
		 */
		const uint64_t& objectNumber() const {
			return _number;
		}
		
		/**
		 Object generation number
		 */
		const uint64_t& generationNumber() const {
			return _gen;
		}
		
		/**
		 Returns the underlying dictionary
		 */
		const MultiVariantDict& dictionary() const {
			return _dict;
		}
		
	protected:
		const char NL = '\n';
		
		uint64_t _number = 0;
        uint64_t _gen = 0;
		
		MultiVariantDict _dict;
		std::weak_ptr<Xref> _xref;
		
		/**
		 Write object begin, '1 0 obj\n'
		 */
		void writeBegin(std::ostream& out) const {
			// Object number -space- Object Generation
			out << _number << ' ' << _gen << ' ' << "obj" << NL;
		}
		
		/**
		 Write object begin, 'endobj\n'
		 */
		void writeEnd(std::ostream& out) const {
			out << NL << "endobj" << NL;
		}
		
		
		friend class Xref;
		/**
		 Change Object id, only call this from Xref
		 */
		void objectNumber(const uint64_t& num) {
			_number = num;
		}
		
        /**
         Set the Object generation number, only call this from Xref
         */
		void generationNumber(const uint64_t& gen) {
			_gen = gen;
		}
	};
}


#endif /* XObject_hpp */

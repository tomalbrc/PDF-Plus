//
//  IndirectObject.hpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 29.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef IndirectObject_hpp
#define IndirectObject_hpp

#include <cstdio>
#include "Object.hpp"
#include "Xref.hpp"

namespace PDF_Plus {
	template <class T>
	class IndirectObject : public Object {
	public:
		using Object::Object;
		
		IndirectObject(const std::weak_ptr<Xref>& parent, const T& initVal) : Object{parent} {
			_t = initVal;
		}
		
		const T& value() const {
			return _t;
		}
		
		void value(const T& t) {
			_t = t;
		}
		
		virtual std::ostream& write(std::ostream& out) override {
			writeBegin(out);
			out << _t;
			writeEnd(out);
			return out;
		}
		
	private:
		T _t = {};
	};
}

#endif /* IndirectObject_hpp */

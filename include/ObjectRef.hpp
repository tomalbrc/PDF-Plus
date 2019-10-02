//
//  ObjectRef.hpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 28.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef ObjectRef_hpp
#define ObjectRef_hpp

#include <cstdio>
#include <type_traits>
#include "Object.hpp"

namespace PDF_Plus {
	/**
	 
	 */
	class ObjectRef {
	public:
		ObjectRef() = default;
		
		/**
		 
		 */
		ObjectRef(const Object* ptr) { _ptr = ptr; }
		
		/**
		 
		 */
		const Object* ptr() const {
			return _ptr;
		}
		
		/**
		 
		 */
		friend std::ostream& operator<<(std::ostream& out, const ObjectRef& objr) {
			return out << objr.ptr()->objectNumber() << ' ' << objr.ptr()->generationNumber() << ' ' << 'R';
		}
	private:
		const Object *_ptr = nullptr;
	};
}

#endif /* ObjectRef_hpp */

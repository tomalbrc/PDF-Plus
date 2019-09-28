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
	class ObjectRef {
	public:
		Object *ptr;
		
		friend std::ostream& operator<<(std::ostream& out, const ObjectRef& objr) {
			return out << objr.ptr->objectNumber() << " 0 " << 'R';
		}
	};
}

#endif /* ObjectRef_hpp */

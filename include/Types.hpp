//
//  Types.hpp
//  PDF-Plus-macOS
//
//  Created by Tom Albrecht on 02.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Types_h
#define Types_h

#include <cstdio>

namespace PDF_Plus {
	/**
	 
	 */
	struct Point {
		int x;
		int y;
		
		Point operator*(float rhs) const {
			auto s = *this;
			s.x *= rhs; s.y *= rhs;
			return s;
		}
	};
	
	/**
	 
	 */
	struct Size {
		int width;
		int height;
		
		Size operator*(float rhs) const {
			auto s = *this;
			s.width *= rhs; s.height *= rhs;
			return s;
		}
	};
	
	/**
	 
	 */
	struct Rect {
		Point origin;
		Size size;
		
		Rect operator*(float rhs) const {
			auto s = *this;
			s.origin = s.origin * rhs; s.size = s.size * rhs;
			return s;
		}
	};
}

#endif /* Types_h */

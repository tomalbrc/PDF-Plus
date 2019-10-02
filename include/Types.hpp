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
	};
	
	/**
	 
	 */
	struct Size {
		int width;
		int height;
	};
	
	/**
	 
	 */
	struct Rect {
		Point origin;
		Size size;
	};
}

#endif /* Types_h */

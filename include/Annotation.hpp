//
//  Annotation.hpp
//  PDF-Plus-macOS
//
//  Created by Tom Albrecht on 03.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Annotation_hpp
#define Annotation_hpp

#include "Object.hpp"
#include "Array.hpp"
#include "ObjectRef.hpp"

namespace PDF_Plus {
	/**
	 
	 */
	class Annotation : public Object {
	public:
		/**
		 
		 */
		Annotation(const std::weak_ptr<Xref>& parent) : Object{parent}
		{
			_dict[Key::Type] = "/Annot";
			_dict[Key::Subtype] = "/Text";
			_dict[Key::Rect] = MultiVariantArray{200, 100, 400, 300};

			_dict[Key::Contents] = String{"Hello, world! This is an Annotation"};
		}
	};
}

#endif /* Annotation_hpp */

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

#include "Types.hpp"

namespace PDF_Plus {
	/**
	 Text Annotation Dictionary
	 */
	class Annotation : public Object {
	public:
		/**
		 Ctor with document xref
		 */
		Annotation(const std::weak_ptr<Xref>& parent,
				   const Rect& rect,
				   const std::string& text = {});
	};
}

#endif /* Annotation_hpp */

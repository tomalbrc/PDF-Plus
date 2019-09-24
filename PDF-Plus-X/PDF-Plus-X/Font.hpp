//
//  Font.hpp
//  PDF-Plus-X
//
//  Created by Mac ERPA on 24.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Font_hpp
#define Font_hpp

#include <stdio.h>
#include "Object.hpp"

namespace PDF_Plus {
	/**
	 Basic Helvetica Font (declared as F1 for PDF-Streams)
	 */
	class Font : public Object {
	public:
		/**
		 
		 */
		Font(const Document* parent) : Object{parent}
		{
			(*this)["Font"] = "<</F1 <</Type /Font /Subtype /Type1 /BaseFont /Helvetica>> >>";
		}
	};
}

#endif /* Font_hpp */

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
		Font(const std::weak_ptr<Xref>& parent) : Object{parent}
		{
			_dict[Key::Type] = "/Font";
			_dict[Key::Subtype] = "/Type1";
			_dict[Key::BaseFont] = "/Helvetica";
		}
	};
}

#endif /* Font_hpp */

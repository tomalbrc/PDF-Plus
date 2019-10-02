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
		struct Properties {
			std::string fontName = "Helvetica";
			int fontSize = 15;
			int kerning = 0; // not implemented yet
			int letterSpacing = 0; // not implemented yet
			int wordSpacing = 0; // not implemented yet
		};
		
		/**
		 
		 */
		Font(const std::weak_ptr<Xref>& parent, const Properties& props) : Object{parent}
		{
			_props = props;
			
			_dict[Key::Type] = "/Font";
			_dict[Key::Subtype] = "/Type1";
			_dict[Key::BaseFont] = "/" + props.fontName;
			
			_resourceName = "F" + std::to_string(objectNumber()+1);
		}
		
		/**
		 Font size
		 */
		Properties properties() const {
			return _props;
		}
		
		/**
		 Set font size
		 */
		void properties(const Properties& props) {
			_props = props;
		}
		
		const std::string& resourceName() const {
			return _resourceName;
		}
	
	private:
		std::string _resourceName;
		Properties _props;
	};
}

#endif /* Font_hpp */

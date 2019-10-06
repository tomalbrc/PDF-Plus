//
//  Annotation.cpp
//  pdfplus
//
//  Created by Tom Albrecht on 03.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include "Annotation.hpp"

namespace PDF_Plus {
	Annotation::Annotation(const std::weak_ptr<Xref>& parent, const Rect& rect, const std::string& text) : Object{parent}
	{
		_dict[Key::Type] = "/Annot";
		_dict[Key::Subtype] = "/Text";
		_dict[Key::Rect] = MultiVariantArray{rect.origin.x, rect.origin.y, rect.size.width, rect.size.height};

		_dict[Key::Contents] = String{text};
	}
}

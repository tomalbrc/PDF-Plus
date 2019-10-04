//
//  Annotation.cpp
//  pdfplus
//
//  Created by Tom Albrecht on 03.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include "Annotation.hpp"

namespace PDF_Plus {
	Annotation::Annotation(const std::weak_ptr<Xref>& parent) : Object{parent}
	{
		_dict[Key::Type] = "/Annot";
		_dict[Key::Subtype] = "/Text";
		_dict[Key::Rect] = MultiVariantArray{200, 100, 400, 300};
		
		_dict[Key::Contents] = String{"Hello, world! This is an Annotation"};
	}
}

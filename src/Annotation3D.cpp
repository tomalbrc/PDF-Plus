//
//  Annotation3D.cpp
//  pdfplus
//
//  Created by Tom Albrecht on 04.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include "Annotation3D.hpp"

namespace PDF_Plus {
	Annotation3D::Annotation3D(const std::weak_ptr<Xref>& parent, const std::string& file) : Object{parent}
	{
		_dict[Key::Type] = "/Annot";
		_dict[Key::Subtype] = "/3D";
		_dict[Key::Rect] = MultiVariantArray{200, 100, 400, 300};
		_dict["Border"] = MultiVariantArray{0, 0, 0};
		_dict["NM"] = String{"RichMedia001"}; // Name
		
		_3dd = std::make_unique<_3DStream>(parent, file);
		
		_dict["3DD"] = ObjectRef{_3dd.get()}; // Name
	}
}

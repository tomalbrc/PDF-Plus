//
//  Annotation3D.cpp
//  pdfplus
//
//  Created by Tom Albrecht on 04.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include "Annotation3D.hpp"

namespace PDF_Plus {
	Annotation3D::Annotation3D(const std::weak_ptr<Xref>& parent, const Rect& rect, const std::string& file) : Annotation{parent, rect}
	{
		_dict[Key::Type] = "/Annot";
		_dict[Key::Subtype] = "/3D";
		_dict[Key::Rect] = MultiVariantArray{rect.origin.x, rect.origin.y, rect.size.width, rect.size.height};
		_dict["Border"] = MultiVariantArray{0, 0, 0};
		_dict["NM"] = String{"_3D_Annot_"+std::to_string(objectNumber())}; // Name
		
		_3dd = std::make_unique<Stream3D>(parent, file);
		_3dv = std::make_unique<View3D>(parent, MultiVariantArray{100.f, 100.f, 160.f}, MultiVariantArray{0.9124869f, -0.3779646f, -0.1565577f, 3.8643272f});
		
		_dict["3DD"] = ObjectRef{_3dd.get()}; // 
		_dict["3DV"] = ObjectRef{_3dv.get()}; //
		_dict["3DA"] = "<</DIS/I/A/PV>>"; //
	}
}

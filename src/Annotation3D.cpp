//
//  Annotation3D.cpp
//  pdfplus
//
//  Created by Tom Albrecht on 04.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include "Annotation3D.hpp"

namespace PDF_Plus {
	Annotation3D::Annotation3D(const std::weak_ptr<Xref>& parent, const std::string& file) : Annotation{parent}
	{
		_dict[Key::Type] = "/Annot";
		_dict[Key::Subtype] = "/3D";
		_dict[Key::Rect] = MultiVariantArray{200, 100, 400, 300};
		_dict["Border"] = MultiVariantArray{0, 0, 0};
		_dict["NM"] = String{"_3D_Annot_"+std::to_string(objectNumber())}; // Name
		
		_3dd = std::make_unique<_3DStream>(parent, file);
		_3dv = std::make_unique<_3DView>(parent, MultiVariantArray{100.f, 100.f, 160.f}, MultiVariantArray{-0.5773502f, 0.5773502f, 0.5773502f, 1.571f});
		
		_dict["3DD"] = ObjectRef{_3dd.get()}; // 
		_dict["3DV"] = ObjectRef{_3dv.get()}; //
		_dict["3DA"] = "<</DIS/I/A/PV>>"; //
	}
}

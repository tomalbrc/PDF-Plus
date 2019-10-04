//
//  3DView.hpp
//  PDF-Plus-macOS
//
//  Created by Tom Albrecht on 04.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef _DView_hpp
#define _DView_hpp

#include <cstdio>
#include "Object.hpp"
#include "ObjectRef.hpp"

namespace PDF_Plus {
	class _3DView : public Object {
	public:
		_3DView(const std::weak_ptr<Xref>& parent) : Object{parent} {
			
			_dict[Key::Type] = "/3DView";
			_dict["XN"] = String{"Default View"}; // External Name (UI)
			_dict["CO"] = 10;
			_dict["MS"] = "/M";
			_dict["NR"] = "true";
			_dict["P"] = "<</Subtype /P /PS /Min /FOV 30.0>>";
			_dict["BG"] = "<</Subtype /SC /C [0.5 0.5 0.5]>>";
		}
		
	};
}

#endif /* _DView_hpp */

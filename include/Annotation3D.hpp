//
//  Annotation3D.hpp
//  pdfplus
//
//  Created by Tom Albrecht on 04.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Annotation3D_hpp
#define Annotation3D_hpp

#include "Annotation.hpp"
#include "ObjectRef.hpp"

#include "Stream3D.hpp"
#include "View3D.hpp"

namespace PDF_Plus {
	/**
	 3D Annotation dictionay
	 */
	class Annotation3D : public Annotation {
	public:
		/**
		 Ctor with document parent and path to U3D file
		 */
		Annotation3D(const std::weak_ptr<Xref>& parent, const Rect& rect, const std::string& file);
		
	private:
		std::unique_ptr<Stream3D> _3dd;
		std::unique_ptr<View3D> _3dv;
	};
}

#endif /* Annotation3D_hpp */

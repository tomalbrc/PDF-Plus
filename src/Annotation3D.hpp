//
//  Annotation3D.hpp
//  pdfplus
//
//  Created by Tom Albrecht on 04.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Annotation3D_hpp
#define Annotation3D_hpp

#include "Object.hpp"
#include "Array.hpp"
#include "ObjectRef.hpp"

#include "3DStream.hpp"

namespace PDF_Plus {
	/**
	 3D Annotation dictionay
	 */
	class Annotation3D : public Object {
	public:
		/**
		 Ctor with document parent and path to U3D file
		 */
		Annotation3D(const std::weak_ptr<Xref>& parent, const std::string& file);
		
	private:
		std::unique_ptr<_3DStream> _3dd;
	};
}

#endif /* Annotation3D_hpp */

//
//  3DStream.hpp
//  pdfplus
//
//  Created by Tom Albrecht on 04.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef _DStream_hpp
#define _DStream_hpp

#include <cstdio>
#include "Stream.hpp"
#include "ObjectRef.hpp"

namespace PDF_Plus {
	class Stream3D : public Stream {
	public:
		Stream3D(const std::weak_ptr<Xref>& parent, const std::string& file);
	};
}

#endif /* _DStream_hpp */

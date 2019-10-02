//
//  Image.hpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 01.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Image_hpp
#define Image_hpp

#include <cstdio>
#include "ObjectRef.hpp"
#include "Stream.hpp"
#include "Keys.hpp"
#include "Types.hpp"

namespace PDF_Plus {
	/**
	Images
	PDF Reference 1.7 Section 4.8.4 "Image Dictionaries"
	*/
	class Image : public Stream {
	public:
		/**
		 
		 */
		struct ImageInfo {
			std::string name = "Im1";
			Size size = {};
			int bits_per_component = 0;
		};
		
		/**
		
		*/
		Image(const std::weak_ptr<Xref>& parent, std::string filepath = {});
		
		/**
		 
		 */
		const ImageInfo& imageInfo() const;
		
	private:
		ImageInfo _iinfo;
		
		void encodeImg(std::string file);
	};
}

#endif /* Image_hpp */

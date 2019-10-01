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
#include "Stream.hpp"

namespace PDF_Plus {
	/**
	Images
	*/
	class Image : public Stream {
	public:
		struct ImageInfo {
			int width = 0;
			int height = 0;
			int bits_per_color = 0;
		};
		
		/**
		
		*/
		Image(const std::weak_ptr<Xref>& parent) : Stream{parent}
		{
			_dict["Type"] = "XObject";
		}
		
		void bytes(const std::vector<std::byte>& data) {
			_data = data;
		}
		
		const std::vector<std::byte>& bytes() const {
			return _data;
		}
		
		void imageInfo(const ImageInfo& imageInfo) {
			_iinfo = imageInfo;
		}
		
		const ImageInfo& imageInfo() const {
			return _iinfo;
		}
		
	private:
		std::vector<std::byte> _data;
		ImageInfo _iinfo;
	};
}

#endif /* Image_hpp */

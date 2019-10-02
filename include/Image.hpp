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
#include "Keys.hpp"

namespace PDF_Plus {
	/**
	Images
	PDF Reference 1.7 Section 4.8.4 "Image Dictionaries"
	*/
	class Image : public Stream {
	public:
		struct ImageInfo {
			std::string name;
			int width = 0;
			int height = 0;
			int bits_per_component = 0;
		};
		
		/**
		
		*/
		Image(const std::weak_ptr<Xref>& parent) : Stream{parent}
		{
			_dict[Key::Type] = "/XObject";
			_dict[Key::Subtype] = "/Image";
			_dict["Width"] = 0;
			_dict["Height"] = 0;
			_dict["BitsPerComponent"] = 8;
			_dict["ColorSpace"] = "DeviceRGB";
			
			using namespace std::literals::string_literals;
			read("q 132 0 0 132 45 140 cm"s + NL + "/Im1 Do Q"s); // Translate 45,140, Scale by 132
		}
		
		void bytes(const std::vector<std::byte>& data) {
			streamData = data;
		}
		
		const std::vector<std::byte>& bytes() const {
			return streamData;
		}
		
		void imageInfo(const ImageInfo& imageInfo) {
			_iinfo = imageInfo;
		}
		
		const ImageInfo& imageInfo() const {
			return _iinfo;
		}
		
	private:
		ImageInfo _iinfo;
	};
}

#endif /* Image_hpp */

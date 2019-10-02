//
//  Image.cpp
//  pdfplus
//
//  Created by Tom Albrecht on 02.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include "Image.hpp"

#include "../lodepng/lodepng.h"

namespace PDF_Plus {
	Image::Image(const std::weak_ptr<Xref>& parent, std::string filepath) : Stream{parent} {
		
		_dict[Key::Type] = "/XObject";
		_dict[Key::Subtype] = "/Image";
		_dict[Key::Width] = 0;
		_dict[Key::Height] = 0;
		_dict[Key::BitsPerComponent] = 8;
		_dict[Key::ColorSpace] = "/DeviceRGB";
		
		if (!filepath.empty()) {
			encodeImg(filepath);
		}
	}
	
	const Image::ImageInfo& Image::imageInfo() const {
		return _iinfo;
	}
	
	void Image::encodeImg(std::string file) {
		
		std::vector<unsigned char> image; //the raw pixels
		unsigned width, height;
		// Always load as 8-bit per channel RGB
		auto error = lodepng::decode(image, width, height, file, LCT_RGB, 8);
		
		if (error) {
			std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		}
		
		std::vector<std::byte> bytes{
			reinterpret_cast<std::byte*>(image.data()),
			reinterpret_cast<std::byte*>(image.data()+image.size())
		};
		
		_iinfo.size.width = width;
		_iinfo.size.height = height;
		_dict[Key::Width] = _iinfo.size.width;
		_dict[Key::Height] = _iinfo.size.height;
		streamData = bytes;
	}
}





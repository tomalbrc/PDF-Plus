//
//  3DStream.cpp
//  pdfplus
//
//  Created by Tom Albrecht on 04.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include "3DStream.hpp"
#include <fstream>

namespace PDF_Plus {
	_3DStream::_3DStream(const std::weak_ptr<Xref>& parent, const std::string& file) : Stream{parent} {
		
		_dict[Key::Type] = "/3D";
		_dict[Key::Subtype] = "/U3D";
		
		std::ifstream fs(file, std::ios::in | std::ios::binary);
		std::vector<char> str((std::istreambuf_iterator<char>(fs)),
							  std::istreambuf_iterator<char>());
		
		streamData.assign(reinterpret_cast<std::byte*>(str.data()),
						  reinterpret_cast<std::byte*>(str.data()+str.size()));
		
	}
}

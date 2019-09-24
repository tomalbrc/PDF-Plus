//
//  Page.hpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 23.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Page_hpp
#define Page_hpp

#include <cstdio>
#include "Object.hpp"
#include "Stream.hpp"
#include "Font.hpp"

namespace PDF_Plus {
	/**
	 
	 */
	class Page : public Object {
	public:
		/**
		 
		 */
		Page(const Document* parent) : Object{parent, "Page"}
		{
			// Din-A4
			(*this)["MediaBox"] = "[0 0 595 842]";
			
			_resources = std::make_shared<Font>(parent);
			(*this)["Resources"] = Object::Ref(_resources.get());
		
			_contents = std::make_shared<Stream>(parent);
			(*this)["Contents"] = Object::Ref(_contents.get());
		}
		
		void setPageSize(int width, int height)
		{
			std::stringstream s;
			s << "[" << 0 << " " << 0 << " " << width << " " << height << "]";
			(*this)["MediaBox"] = s.str();
		}
		
		/**
		 
		 */
		std::shared_ptr<Stream> contents()
		{
			return _contents;
		}
		
	private:
		std::shared_ptr<Stream> _contents;
		std::shared_ptr<Font> _resources;
	};
}

#endif /* Page_hpp */

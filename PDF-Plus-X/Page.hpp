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
#include "ObjectRef.hpp"
#include "Stream.hpp"
#include "Font.hpp"

namespace PDF_Plus {
	/**
	 
	 */
	class Page : public Object {
	public:
		/**
		 
		 */
		Page(const std::weak_ptr<Xref>& parent) : Object{parent}
		{
			// Din-A4
			(*this)[Key::Type] = "/Page";
			(*this)[Key::MediaBox] = MultiVariantArray{{0, 0, 595, 842}};
			(*this)[Key::TrimBox] = MultiVariantArray{{2, 2, 595-4, 842-4}};

			_resources = std::make_shared<Font>(parent);
			(*this)["Resources"] = ObjectRef{_resources.get()};
		
			_contents = std::make_shared<Stream>(parent);
			(*this)["Contents"] = ObjectRef{_contents.get()};
            
            (*this)["Rotate"] = "0";
		}
		
		void setPageSize(int width, int height)
		{
			(*this)[Key::MediaBox] = MultiVariantArray{{0, 0, width, height}};
			(*this)[Key::MediaBox] = MultiVariantArray{{0, 0, width, height}};
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

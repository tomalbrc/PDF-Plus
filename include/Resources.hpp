//
//  Resources.hpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 01.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Resources_hpp
#define Resources_hpp

#include <cstdio>
#include "Font.hpp"
#include "Image.hpp"

namespace PDF_Plus {
	/**
	Resource Dictionary (Object) for a page
	*/
	class Resources : public Object {
	public:
		/**
		
		*/
		Resources(const std::weak_ptr<Xref>& parent) : Object{parent}
		{
			// Required dict entries here
		}
		
		/**
		 
		 */
		virtual std::ostream& write(std::ostream& out) override {
			{
				std::ostringstream oss;
				oss << _fonts;
				_dict[Key::Font] = oss.str();
			}
			{
				std::ostringstream oss;
				oss << _images;
				if (oss.str().size() > 5)
					_dict[Key::XObject] = oss.str();
			}
			
			return Object::write(out);
		}
		
		/**
		 
		 */
		void addImage(const std::shared_ptr<Image>& image) {
			_images[image->imageInfo().name] = ObjectRef{image.get()};
			_resStrongRef.push_back(image);
		}
		
		/**
		 
		 */
		void addFont(const std::shared_ptr<Font>& font) {
			_fonts[font->resourceName()] = ObjectRef{font.get()};
			_resStrongRef.push_back(font);
		}

	private:
		Dictionary<ObjectRef> _fonts; // references to font objects
		Dictionary<ObjectRef> _images; // references to image xobjects
		
		std::vector<std::shared_ptr<Object>> _resStrongRef;
	};
}

#endif /* Resources_hpp */

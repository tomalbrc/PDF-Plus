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
		void addImage(const std::weak_ptr<Image>& image) {
			_images[image.lock()->imageInfo().name] = ObjectRef{image.lock().get()};
		}
		
		/**
		 
		 */
		void addFont(const std::weak_ptr<Font>& font) {
			_fonts[font.lock()->resourceName()] = ObjectRef{font.lock().get()};
		}

	private:
		Dictionary<ObjectRef> _fonts; // references to font objects
		Dictionary<ObjectRef> _images; // references to image xobjects
		
		std::shared_ptr<Font> baseFont;
	};
}

#endif /* Resources_hpp */

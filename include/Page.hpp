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
#include "Resources.hpp"
#include "Annotation.hpp"

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
			_dict[Key::Type] = "/Page";
			setPageSize(595, 842); // DIN A4
			setRotate(0);
			
			_resources = std::make_shared<Resources>(parent);
			_dict[Key::Resources] = ObjectRef{_resources.get()};
		
			_contents = std::make_shared<Stream>(parent);
			_dict[Key::Contents] = ObjectRef{_contents.get()};
		}
		
		/**
		 
		 */
		void setPageSize(int width, int height)
		{
			_dict[Key::MediaBox] = MultiVariantArray{0, 0, width, height};
			_dict[Key::TrimBox] = MultiVariantArray{0, 0, width, height};
		}
		
		/**
		 
		 */
		void setRotate(int r)
		{
			_dict[Key::Rotate] = r;
		}
		
		/**
		 
		 */
		std::shared_ptr<Stream> contents() const
		{
			return _contents;
		}
		
		/**
		 
		 */
		std::shared_ptr<Resources> resources() const
		{
			return _resources;
		}
		
		void addAnnotation(const std::shared_ptr<Annotation>& annot) {
			_annotsStrongRef.push_back(annot);
			
			if (!std::holds_alternative<MultiVariantArray>(_dict["Annots"])) {
				_dict["Annots"] = MultiVariantArray{};
			}
			
			auto& annots = std::get<MultiVariantArray>(_dict["Annots"]);
			annots.append(ObjectRef{annot.get()});
		}
		
	private:
		std::shared_ptr<Stream> _contents;
		std::shared_ptr<Resources> _resources;
		
		std::vector<std::shared_ptr<Annotation>> _annotsStrongRef;
	};
}

#endif /* Page_hpp */

//
//  Catalog.hpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 23.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Catalog_hpp
#define Catalog_hpp

#include <cstdio>
#include "Object.hpp"
#include "ObjectRef.hpp"
#include "Pages.hpp"
#include "Page.hpp"
#include "Keys.hpp"

namespace PDF_Plus {
	/**
	 
	 */
	class Catalog : public Object {
	public:
		/**
		 
		 */
		Catalog(const std::weak_ptr<Xref>& parent) :
			Object{parent}
		{
			_dict[Key::Type] = "/Catalog";
			_pages = std::make_shared<Pages>(parent);
			_dict[Key::Pages] = ObjectRef{_pages.get()};
		}
		
		/**
		 
		 */
		const std::shared_ptr<Pages>& pages()
		{
			return _pages;
		}
		
	private:
		std::shared_ptr<Pages> _pages;
	};
}

#endif /* Catalog_hpp */

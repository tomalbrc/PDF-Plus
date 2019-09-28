//
//  Pages.hpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 23.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Pages_hpp
#define Pages_hpp

#include <stdio.h>
#include "Object.hpp"
#include "ObjectRef.hpp"
#include "Array.hpp"
#include "Page.hpp"

namespace PDF_Plus {
	/**
	 
	 */
	class Pages : public Object {
	public:
		/**
		 
		 */
		Pages(const std::weak_ptr<Xref>& parent) : Object{parent}
		{
			(*this)["Type"] = "/Pags";
			(*this)["Kids"] = MultiVariantArray{};
		}
		
		/**
		 
		 */
		void add(const std::shared_ptr<Page>& page)
		{
			(*page)["Parent"] = ObjectRef{this};
			_pageList.emplace_back(page);
			
			(*this)["Count"] = std::to_string(_pageList.size());
			
			std::get<MultiVariantArray>((*this)["Kids"]).append(ObjectRef{page.get()});
		}
		
	private:
		std::vector<std::shared_ptr<Page>> _pageList;
	};
}

#endif /* Pages_hpp */

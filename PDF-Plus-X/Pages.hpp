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
			_dict["Type"] = "/Pags";
			_dict["Kids"] = MultiVariantArray{};
		}
		
		/**
		 
		 */
		void add(const std::shared_ptr<Page>& page)
		{
			(*page)["Parent"] = ObjectRef{this};
			_pageList.emplace_back(page);
			
			_dict["Count"] = std::to_string(_pageList.size());
			
			std::get<MultiVariantArray>(_dict["Kids"]).append(ObjectRef{page.get()});
		}
		
	private:
		std::vector<std::shared_ptr<Page>> _pageList;
	};
}

#endif /* Pages_hpp */

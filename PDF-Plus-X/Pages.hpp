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
			_dict[Key::Type] = "/Pages";
			_dict[Key::Kids] = MultiVariantArray{};
		}
		
		/**
		 
		 */
		void add(const std::shared_ptr<Page>& page)
		{
			(*page)[Key::Parent] = ObjectRef{this};
			_pageList.emplace_back(page);
			
			_dict[Key::Count] = std::to_string(_pageList.size());
			
			auto& kids = std::get<MultiVariantArray>(_dict[Key::Kids]);
			kids.append(ObjectRef{page.get()});
		}
		
	private:
		std::vector<std::shared_ptr<Page>> _pageList;
	};
}

#endif /* Pages_hpp */

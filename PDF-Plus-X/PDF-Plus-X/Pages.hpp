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
#include "Page.hpp"

class Pages : public Object {
public:
	Pages(const Document *parent) : Object{parent, "Pages"}
	{
		
	}
	
	friend std::ostream& operator<<(std::ostream& out, const Pages& obj)
	{
		out << (Object)obj;
		for (auto& page: obj._pageList)
			out << *page;
		return out;
	}
	
	void add(const std::shared_ptr<Page>& page)
	{
		_pageList.emplace_back(page);
	}
	
private:
	std::vector<std::shared_ptr<Page>> _pageList;
};

#endif /* Pages_hpp */

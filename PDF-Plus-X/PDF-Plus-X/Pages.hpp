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
		(*this)["MediaBox"] = "[0 0 500 800]";
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
		(*page)["Parent"] = Object::Ref(this);
		_pageList.emplace_back(page);
		
		(*this)["Count"] = std::to_string(_pageList.size());
		
		// TODO: Add ALL kids!!
		std::string kids = "[";
		for (auto& p: _pageList)
			kids += Object::Ref(p.get()) + " ";
		
		kids += "]";
		(*this)["Kids"] = kids;
	}
	
private:
	std::vector<std::shared_ptr<Page>> _pageList;
};

#endif /* Pages_hpp */

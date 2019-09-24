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

class Page : public Object {
public:
	Page(const Document *parent) : Object{parent, "Page"}
	{
		(*this)["Resources"] = "<< >>";
	}
	
	void drawLine()
	{
		
	}
	
	void drawText()
	{
		
	}
	
	void drawImage()
	{
		
	}
	
	void draw3D()
	{
		// Universal 3D
	}
	
private:
};

#endif /* Page_hpp */

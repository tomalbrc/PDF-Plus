//
//  main.cpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 22.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "Dict.hpp"
#include "Document.hpp"
#include "Object.hpp"
#include "Catalog.hpp"

int main(int argc, const char * argv[])
{
	using namespace PDF_Plus;
	
	auto doc = std::make_unique<Document>(Document::Version{"1.4"});
	
	auto page = std::make_shared<Page>(doc.get());
	page->contents()->drawText("Page 1", 10, 10, 10);
	page->contents()->drawText("Hello, world!", 100, 300, 30);
	page->contents()->drawRect(10, 10, 110, 110);
	doc->addPage(page);
	
	auto page2 = std::make_shared<Page>(doc.get());
	page2->contents()->drawText("Page 2", 10, 10, 10);
	page2->contents()->drawLine(0,0, 500,800);
	doc->addPage(page2);
	
	auto page3 = std::make_shared<Page>(doc.get());
	page3->contents()->drawText("Page 3", 10, 10, 10);
	page3->contents()->drawLine(0,400, 500,400);
	doc->addPage(page3);
	
	std::ofstream ofs;
	ofs.open("/tmp/MyRanda.pdf");
	doc->write(std::cout);
	doc->write(ofs);
	
	return 0;
}



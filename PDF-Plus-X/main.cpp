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

void make_table(PDF_Plus::Page *page)
{
	int hc = 7;
	int h = 40;
	
	int wc = 6;
	int w = 90;
	for (int i = 1; i <= wc; i++) {
		page->contents()->drawLine(i*w,h,		i*w,h*hc);
	}
	
	for (int i = 1; i <= hc; i++) {
		page->contents()->drawLine(w,i*h,		w*wc,i*h);
	}
	
	for (int i = 1; i <= wc-1; i++) {
		for (int j = 1; j <= hc-1; j++) {
			page->contents()->drawText(std::to_string(i)+" "+std::to_string(hc-j),
									   i*w+10,//x
									   j*h+10,//y
									   12);//font
		}
	}
}

int main(int argc, const char * argv[])
{
	using namespace PDF_Plus;
	
	auto doc = std::make_unique<Document>(Document::Version{"1.4"});
	
	auto page = std::make_shared<Page>(doc.get());
	page->contents()->drawText("Page 1", 10, 10, 10);
	page->contents()->drawText("Hello, world!", 100, 300, 30);
	
	make_table(page.get());
	
	doc->addPage(page);
	
	auto page2 = std::make_shared<Page>(doc.get());
	page2->contents()->drawText("Page 2", 10, 10, 10);
	page2->contents()->drawLine(0,0, 500,800);
	page2->contents()->drawRect(10, 10, 110, 110);
	doc->addPage(page2);
	
	auto page3 = std::make_shared<Page>(doc.get());
	page3->contents()->drawText("Page 3", 10, 10, 10);
	page3->contents()->drawLine(0,400, 500,400);
	doc->addPage(page3);
	
	std::ofstream ofs;
	ofs.open("/tmp/pdfplus.pdf");
	doc->write(std::cout);
	doc->write(ofs);
	
	return 0;
}

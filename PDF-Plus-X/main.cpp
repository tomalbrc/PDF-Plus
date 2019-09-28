//
//  main.cpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 22.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "Dictionary.hpp"
#include "Document.hpp"
#include "Object.hpp"
#include "Catalog.hpp"

#include "Array.hpp"
#include "String.hpp"



void make_table(PDF_Plus::Page *page)
{
	int x = 0;
	int y = 400;
	
	int hc = 8;
	int h = 30;
	
	int wc = 6;
	int w = 90;
	for (int i = 1; i <= wc; i++) {
		page->contents()->drawLine(i*w+x,h+y,		i*w+x,h*hc+y);
	}
	
	for (int i = 1; i <= hc; i++) {
		page->contents()->drawLine(w+x,i*h+y,		w*wc+x,i*h+y);
	}
	
	std::vector<std::vector<std::string>> plan{
		{"PR", "DR", "RU", "PR", "LU"},
		{"AB", "VA", "LU", "LU", "PR"},
		{"RU", "BR", "AB", "VA", "SG"},
		{"RU", "DR", "-", "-", "SG"},
	};
	
	for (int i = 1; i <= wc-1; i++) {
		for (int j = 1; j <= hc-1; j++) {
			auto text = plan[(hc-j-1)/2][i-1];
			page->contents()->drawText(text,
									   x+i*w+10,//x
									   y+j*h+10,//y
									   12);//font
		}
	}
}

int main(int argc, const char * argv[])
{
	using namespace PDF_Plus;
	
	auto doc = std::make_unique<Document>(Document::Version{"1.6"});
	
	auto page = std::make_shared<Page>(*doc);
	page->contents()->drawText("Page 1", 10, 10, 10);
	page->contents()->drawText("Hello, world!", 100, 750, 30);
	page->contents()->drawRect(100-10, 750-10, 200, 50);
	make_table(page.get());
	
	doc->addPage(page);
	
	auto page2 = std::make_shared<Page>(*doc);
	page2->contents()->drawText("Page 2", 10, 10, 10);
	page2->contents()->drawLine(0,0, 500,800);
	page2->contents()->drawRect(160, 210, 110, 110);
	doc->addPage(page2);
	
	
	std::ofstream ofs;
	ofs.open("/tmp/pdfplus.pdf");
	std::cout << *doc;
	ofs << *doc;

	
	return 0;
}

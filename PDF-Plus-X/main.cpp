//
//  main.cpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 22.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "PDF_Plus.h"

void make_class(int x, int y, std::string title, std::vector<std::string> fcs, PDF_Plus::Page *page) {
	int h = 40+static_cast<int>(fcs.size())*15;
	int w = 200;
	page->contents()->drawRect(x, y, w, h);
	page->contents()->drawText(title, x+5, y + h - 20, 15);
	page->contents()->drawLine(x+5, y + h -25, x+5 + w-10, y+h-25);
	
	int i = 0;
	for (auto& f: fcs) {
		i++;
		page->contents()->drawText(f, x+5, y + h - 30 - 15*i, 13);
	}
}

/**
 Example Timetable
 */
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
									   12);//font size
		}
	}
}

int main(int argc, const char * argv[])
{
	using namespace PDF_Plus;
	
	auto doc = std::make_unique<Document>(Document::Version{"1.6"});
	
	auto page = std::make_shared<Page>(*doc);
	page->contents()->drawText("Page 1", 10, 10, 10);
	page->contents()->drawText("Timetable", 100, 750, 30);
	page->contents()->drawRect(100-10, 750-10, 5*90, 50);
	make_table(page.get());
	doc->addPage(page);
	
	auto page2 = std::make_shared<Page>(*doc);
	page2->contents()->drawText("Page 2", 10, 10, 10);
	page2->contents()->drawText("Class Diagram", 100, 750, 30);
	page2->contents()->drawRect(100-10, 750-10, 5*90, 50);
	
	make_class(90, 600, "Array", {"set()", "get<Get_t>()"}, page2.get());
	make_class(90, 520, "Dictionary", {"set()", "get<Get_t>()"}, page2.get());
	make_class(90, 440, "Object", {"set()", "get<Get_t>()"}, page2.get());
	make_class(90, 360, "Document", {"set()", "get<Get_t>()"}, page2.get());
	make_class(90, 270, "DocumentInfo", {"set()", "get<Get_t>()"}, page2.get());
	make_class(90, 190, "Catalog", {"set()", "get<Get_t>()"}, page2.get());
	make_class(300, 600, "Page", {"set()", "get<Get_t>()"}, page2.get());
	make_class(300, 520, "Pages", {"set()", "get<Get_t>()"}, page2.get());
	make_class(300, 440, "Stream", {"set()", "get<Get_t>()"}, page2.get());
	make_class(300, 360, "Font", {"set()", "get<Get_t>()"}, page2.get());
	make_class(300, 270, "ObjectRef", {"set()", "get<Get_t>()"}, page2.get());
	make_class(300, 190, "IndirectObject", {"set()", "get<Get_t>()"}, page2.get());

	doc->addPage(page2);
	
	std::ofstream ofs;
	ofs.open("/tmp/pdfplus.pdf", std::ios::binary);
	std::cout << *doc;
	ofs << *doc;
	
	return 0;
}

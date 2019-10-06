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

void make_class(std::weak_ptr<PDF_Plus::Font>font,
				PDF_Plus::Point p,
				std::string title,
				std::vector<std::string> fcs,
				PDF_Plus::Page *page)
{
	
	using namespace PDF_Plus;

	int h = 40+static_cast<int>(fcs.size())*15;
	int w = 200;
	page->contents()->drawRect({p, {w, h}});
	
	page->contents()->drawText(title,
							   font,
							   {p.x+5, p.y + h - 20});
	
	page->contents()->drawLine({p.x+5, p.y + h -25},
							   {p.x+5 + w-10, p.y+h-25});
	
	int i = 0;
	for (auto& f: fcs) {
		i++;
		page->contents()->drawText(f, font, {p.x+5, p.y + h - 30 - 15*i});
	}
}

/**
 Example Timetable
 */
void make_table(std::weak_ptr<PDF_Plus::Font>f, PDF_Plus::Page *page)
{
	using namespace PDF_Plus;
	
	int x = 0;
	int y = 400;
	
	int hc = 8;
	int h = 30;
	
	int wc = 6;
	int w = 90;
	for (int i = 1; i <= wc; i++) {
		page->contents()->drawLine(Point{i*w+x,h+y},		Point{i*w+x,h*hc+y});
	}
	
	for (int i = 1; i <= hc; i++) {
		page->contents()->drawLine(Point{w+x,i*h+y},		Point{w*wc+x,i*h+y});
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
			page->contents()->drawText(text, f,
									   Point{x+i*w+10, y+j*h+10});
		}
	}
}

int main(int argc, const char * argv[])
{
	using namespace PDF_Plus;
	
	auto doc = std::make_unique<Document>("Example Document");
	
	auto bigfont = std::make_shared<Font>(*doc, Font::Properties{
		.fontSize = 25
	});
	auto font = std::make_shared<Font>(*doc, Font::Properties{
		.fontSize = 14,
		.fontName = "Courier"
	});
	
	auto image = std::make_shared<Image>(*doc, "parrot-portrait-karen-arnold.png");
	auto textAnnot = std::make_shared<Annotation>(*doc, Rect{100,600,400,400}, "MyText");
	auto ann = std::make_shared<Annotation3D>(*doc, Rect{100,100,400,400}, "teapot.u3d");

	auto page = std::make_shared<Page>(*doc);
	page->resources()->addFont(bigfont);
	page->resources()->addFont(font);
	page->resources()->addImage(image);
	page->addAnnotation(ann);
	page->contents()->drawText("Page 1", font, Point{10, 10});
	page->contents()->drawText("Timetable", bigfont, Point{100, 750});
	page->contents()->drawRect(Rect{100-10, 750-10, 450, 50});
	page->contents()->drawRect(Rect{100, 100, 300, 300});
	page->contents()->drawImage(image, Point{100, 400}, image->imageInfo().size*.5f);
	make_table(font, page.get());
	doc->addPage(page);
	
	auto page2 = std::make_shared<Page>(*doc);
	page2->resources()->addFont(bigfont);
	page2->resources()->addFont(font);
	page2->resources()->addImage(image);
	page2->contents()->drawImage(image, Point{100, 500}, image->imageInfo().size*1.f);

	page2->contents()->drawText("Page 2", font, Point{10, 10});
	page2->contents()->drawText("Class Diagram", bigfont, Point{100, 755});
	page2->contents()->drawRect(Rect{100-10, 750-10, 410, 50});
	
	make_class(font, Point{90, 600}, "Array", {"+ set()", "+ get<Get_t>()"}, page2.get());
	make_class(font, Point{90, 520}, "Dictionary", {"set()", "get<Get_t>()"}, page2.get());
	make_class(font, Point{90, 440}, "Object", {"set()", "get<Get_t>()"}, page2.get());
	make_class(font, Point{90, 360}, "Document", {"set()", "get<Get_t>()"}, page2.get());
	make_class(font, Point{90, 280}, "DocumentInfo", {"set()", "get<Get_t>()"}, page2.get());
	make_class(font, Point{90, 200}, "Catalog", {"set()", "get<Get_t>()"}, page2.get());
	make_class(font, Point{300, 600}, "Page", {"set()", "get<Get_t>()"}, page2.get());
	make_class(font, Point{300, 520}, "Pages", {"set()", "get<Get_t>()"}, page2.get());
	make_class(font, Point{300, 440}, "IndirectObject", {"value()", "write()"}, page2.get());
	make_class(font, Point{300, 360}, "Font", {"set()", "get<Get_t>()"}, page2.get());
	make_class(font, Point{300, 280}, "ObjectRef", {"set()", "get<Get_t>()"}, page2.get());
	make_class(font, Point{300, 200-45}, "Stream", {"+ drawText()", "+ drawLine()", "+ drawRect()", "+ write()", "+ size()"}, page2.get());

	doc->addPage(page2);
	
	std::ofstream ofs;
	ofs.open("/tmp/pdfplus.pdf", std::ios::binary);
	std::cout << *doc;
	ofs << *doc;
	
	return 0;
}

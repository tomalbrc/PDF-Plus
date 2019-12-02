# PDF+ / PDF-Plus

### pi-di-ɛf+
> Creating and writing PDF files using c++
#

### Motivation

The goal is to learn enough about the PDF specification
and in the end be able to generate PDF files with 3D/Multimedia support.

#

### Compile

You'll need a compiler that supports C++17 (C++1z)

Tested with Apple Clang 11, Clang 8.0.0 on Debian Linux and Visual Studio 2017

A cmake solution is on the way

#

### TODO
- [ ] PDF Parsing/Reading
- [ ] Metadata support
- [ ] Wiki
- [ ] Documentation
- [x] ~~Image support~~
- [x] ~~Annotations for Pages~~
- [x] ~~3D Support~~
- [x] ~~Stronger types (much is stringly typed a.t.m., see `PDF_Plus::Object::Ref` for example)~~
- [x] ~~Better stream handling~~
- [x] ~~Implement stream compression~~

#

### Usage
*Example usage:*
```
#include "PDF_Plus.h"
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
		
	auto page = std::make_shared<Page>(*doc);
	page->resources()->addFont(bigfont);
	page->resources()->addFont(font);
	page->contents()->drawText("Page 1", font, Point{10, 10});
	page->contents()->drawText("Timetable", bigfont, Point{100, 750});
	doc->addPage(page);
		
	std::ofstream ofs;
	ofs.open("/tmp/pdfplus.pdf", std::ios::binary);
	std::cout << *doc;
	ofs << *doc;
	
	return 0;
}
```

#

### Resources:
[PDF Reference](https://www.adobe.com/content/dam/acom/en/devnet/acrobat/pdfs/pdf_reference_1-7.pdf)  
[CMAKE examples](https://cmake.org/examples/)

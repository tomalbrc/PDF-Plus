# PDF+ / PDF-Plus

### pi-di-ɛf+
> Creating and writing PDF files using c++
#

### Motivation

The goal is to learn enough about the PDF specification
and in the end be able to generate PDF files with 3D/Multimedia support.
Conformance with a PDF Standard is also a goal for this library.
  
Feel free to contribute :)

#

### Compile

You'll need a compiler that supports C++17 (C++1z)
`std::filesystem` is not being used here (yet)

Tested with Apple Clang 11, Clang 8.0.0 on Debian Linux and Visual Studio 2017

#

### TODO
- [ ] Image support
- [ ] Annotations for Pages
- [ ] 3D Support
- [ ] Metadata support
- [ ] Wiki
- [ ] Documentation
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
[PDF Reference](https://www.adobe.com/content/dam/acom/en/devnet/pdf/pdfs/pdf_reference_archives/PDFReference.pdf)  
[Lightweight python implementation used for reference & Diagrams related to the PDF structure](https://github.com/feliam/miniPDF/blob/master/README.md)  
[Handmade PDF (by idrsolutions)](https://blog.idrsolutions.com/2010/10/make-your-own-pdf-file-part-4-hello-world-pdf/)  
[Adobe Supplement to ISO 32000](https://www.adobe.com/content/dam/acom/en/devnet/acrobat/pdfs/adobe_supplement_iso32000.pdf)  
[CMAKE examples](https://cmake.org/examples/)


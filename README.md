

# PDF+ / PDF-Plus

### pi-di-ɛf+
> Creating and writing PDF files using c++
#

### Motivation

The goal is to learn enough about the PDF specification
and in the end be able to generate PDF files with 3D/Multimedia support.
I'm not aiming for PDF/A or PDF/* conformance.
Important is that at least Adobe's Acrobat Reader can read a generated PDF file.
  
Feel free to contribute :)

#

### Compile

You'll need a compiler that supports C++17 (C++1z)
`std::filesystem` is not being used here (yet)
Tested with Apple Clang 11

#

### TODO
* Annotations for Pages
* Better `obj` referencing
* Easier Arrays
* Templated `Object` (`obj` can be an array or dict etc..)
* 3D Support
* Image support
* Metadata support
* Stronger types (much is stringly typed a.t.m., see `PDF_Plus::Object::Ref` for example)
* Better stream handling
* Implement stream encoding/compression

#

### Usage
*Example usage:*
```
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
	ofs.open("/tmp/pdf_plus.pdf");
	doc->write(std::cout);
	doc->write(ofs);
	
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


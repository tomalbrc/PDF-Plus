

# PDF+ / PDF-Plus

### pi-di-ɛf+
- The art of writing PDF files using c++
##
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

Resources:
[PDF Reference](https://www.adobe.com/content/dam/acom/en/devnet/pdf/pdfs/pdf_reference_archives/PDFReference.pdf)
[Nice Diagrams related to the PDF structure](https://github.com/feliam/miniPDF/blob/master/README.md)
[Handmade PDF](https://blog.idrsolutions.com/2010/10/make-your-own-pdf-file-part-4-hello-world-pdf/)


[CMAKE examples](https://cmake.org/examples/)


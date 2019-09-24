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

int main(int argc, const char * argv[]) {

	auto doc = std::make_unique<Document>("1.7");

	auto page = std::make_shared<Page>(doc.get());
	auto page2 = std::make_shared<Page>(doc.get());

	doc->addPage(page);
	doc->addPage(page2);

	std::cout << *doc;

	std::ofstream ofs;
	ofs.open("/tmp/MyRanda.pdf");
	ofs << doc;
	
	return 0;
}


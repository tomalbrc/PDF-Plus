//
//  Document.hpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 22.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Document_hpp
#define Document_hpp

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <cmath>

#include "Catalog.hpp"
#include "Page.hpp"

class Document {
public:
	using Version = std::string;
	
	Document(const Version& docVersion)
	{
		_docVersion = docVersion;
		_catalog = std::make_shared<Catalog>(this);
	}
	
	void addPage(const std::shared_ptr<Page>& p)
	{
		_catalog->pages()->add(p);
	}
	
	friend std::ostream& operator<<(std::ostream& out, const Document& d)
	{
		const auto NL = '\n';
		out << "%PDF-" << d._docVersion << NL;
		//out << "%" << (char)0xE7 << (char)0xF3 << (char)0xCF << (char)0xD3 << NL;
		
		out << *d._catalog;
		
		//out << d._xref;
		d.writeXRef(out);
		out << "%%EOF" << NL;
		return out;
	}
	
private:
	Version _docVersion;
	std::shared_ptr<Catalog> _catalog;
	
	
	// XRef table impl.
	mutable std::vector<std::weak_ptr<Object>> xrefList{};
	friend class Object;
	void addObject(std::weak_ptr<Object> obj) const
	{
		if (auto o = obj.lock())
		{
			o->setIdentifier(xrefList.size()+1);
			xrefList.emplace_back(obj);
		}
		else
		{
			std::cout << "Object was released?!" << std::endl;
		}
	}
	
	void writeXRef(std::ostream& out) const
	{
		out << "xref" << '\n';
		out << "0 " << xrefList.size()+1 << '\n';
		out << "0000000000 " << std::pow(2,16)-1 << " f" << '\n';
		
		std::size_t off = 0;
		for (auto& o: xrefList)
		{
			if (auto obj = o.lock())
			{
				off += obj->size();
				out << std::setw(10) << std::setfill('0') << off << " 00000 n" << '\n';
			}
			else
			{
				std::cout << "Ptr invalid" << std::endl;
			}
		}

		out << "trailer <</Size " << xrefList.size()+1 << " /Root 1 0 R>>" << '\n';
		out << "startxref" << '\n';
		out << "9" << '\n';
	}
};

#endif /* Document_hpp */

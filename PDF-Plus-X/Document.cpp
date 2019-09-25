//
//  Document.cpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 24.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include "Document.hpp"

namespace PDF_Plus {
	
	Document::Document(const Version& docVersion)
	{
		_docVersion = docVersion;
		_catalog = std::make_shared<Catalog>(this);
		
		_headerOffset = generateHeader().length();
	}
	
	/**
	 
	 */
	void Document::addPage(const std::shared_ptr<Page>& p)
	{
		_catalog->pages()->add(p);
	}
	
	/**
	 
	 */
	void Document::write(std::ostream& out) const
	{
		const auto NL = '\n';
		out << generateHeader();
		
		// Write every object
		for (const auto& obj: xrefList)
			obj->write(out);
		
		writeXRef(out);
		out << "%%EOF" << NL;
	}

	/// MARK: Private

	std::string Document::generateHeader() const
	{
		std::stringstream out;
		out << "%PDF-" << _docVersion << '\n';
		// Signal to readers that this file contains binary data
		out << "%" << (char)0xE7 << (char)0xF3 << (char)0xCF << (char)0xD3 << '\n';
		return out.str();
	}

	/// MARK: XRef
	void Document::addObject(Object* obj) const
	{
		obj->setIdentifier(xrefList.size()+1);
		xrefList.emplace_back(obj);
	}
	void Document::removeObject(Object* obj) const
	{
		xrefList.erase(std::remove(xrefList.begin(), xrefList.end(), obj), xrefList.end());
	}
	
	void Document::writeXRef(std::ostream& out) const
	{
		std::stringstream ss;
		_catalog->write(ss);

		out << "xref" << '\n';
		out << "0 " << xrefList.size()+1 << '\n';
		out << "0000000000 " << std::pow(2,16)-1 << " f" << '\n';

		std::size_t off = 0;
		for (auto& o: xrefList)
		{
			out << std::setw(10) << std::setfill('0') << off+_headerOffset << " 00000 n" << '\n';
			off += o->size();
		}

		out << "trailer <</Size " << xrefList.size()+1 << " /Root 1 0 R>>" << '\n';
		out << "startxref" << '\n';
		out << off + _headerOffset << '\n'; // Directly After Header
	}
}

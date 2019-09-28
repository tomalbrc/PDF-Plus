//
//  Document.cpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 24.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include "Document.hpp"
#include "DocumentInfo.hpp"

namespace PDF_Plus {
	
	Document::Document(const Version& docVersion)
	{
		_xref = std::make_shared<Xref>();

		_docVersion = docVersion;
		_catalog = std::make_unique<Catalog>(this);
		_info = std::make_unique<DocumentInfo>(this, "Demo PDF");

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
		for (const auto& obj: *_xref)
			obj->write(out);
		
		_xref->write(out, _headerOffset, Object::Ref(_info.get()));
		out << "%%EOF" << NL;
	}

	/// MARK: Private

	std::string Document::generateHeader() const
	{
		std::stringstream out;
		out << "%PDF-" << _docVersion << '\n';
		// Signal to readers that this file contains binary data
		out << "%" << (char)0xE2 << (char)0xE3 << (char)0xCF << (char)0xD3 << '\n';
		return out.str();
	}
}

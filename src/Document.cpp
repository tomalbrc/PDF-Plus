//
//  Document.cpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 24.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include "Document.hpp"
#include "DocumentInfo.hpp"

#include "ObjectRef.hpp"

namespace PDF_Plus {
	
	Document::Document(const std::string& title)
	{
		_xref = std::make_shared<Xref>();

		_catalog = std::make_unique<Catalog>(_xref);
		_info = std::make_unique<DocumentInfo>(_xref, title);

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
	std::ostream& Document::write(std::ostream& out) const
	{
		const auto NL = '\n';
	
		out << generateHeader();
		
		// Write every object
		for (const auto& obj: *_xref)
			obj->write(out);
		
		_xref->write(out, _headerOffset, ObjectRef{_info.get()});
		out << "%%EOF" << NL;
		
		return out;
	}

	std::ostream& operator<<(std::ostream &out, const 	PDF_Plus::Document &d) {
		return d.write(out);
	}

	std::weak_ptr<Xref> Document::xref() const {
		return _xref;
	}

	Document::operator std::weak_ptr<Xref>() {
		return _xref;
	}

	/// MARK: Private

	std::string Document::generateHeader() const
	{
		std::stringstream out;
		out << "%PDF-" << "1.7" << '\n';
		// Signal to readers that this file contains binary data
		out << "%" << (char)0xE2 << (char)0xE3 << (char)0xCF << (char)0xD3 << '\n';
		return out.str();
	}
}

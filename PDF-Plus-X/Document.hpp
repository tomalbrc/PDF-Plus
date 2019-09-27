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

#include "Xref.hpp"
#include "DocumentInfo.hpp"
#include "Catalog.hpp"
#include "Page.hpp"

namespace PDF_Plus {
	/**
	 
	 */
	class Document {
	public:
		using Version = std::string;
		
		/**
		 
		 */
		Document(const Version& docVersion);
		
		/**
		 
		 */
		void addPage(const std::shared_ptr<Page>& p);
		
		/**
		 
		 */
		virtual void write(std::ostream& out) const;
		
		std::weak_ptr<Xref> xref() const
		{
			return _xref;
		}
		
	private:
		std::size_t _headerOffset = 0;
		Version _docVersion;
        std::unique_ptr<Catalog> _catalog;
		std::unique_ptr<DocumentInfo> _info;
		std::shared_ptr<Xref> _xref;

		/**
		 Returns the PDF file header (with magic numbers)
		 */
		std::string generateHeader() const;
	};

}

#endif /* Document_hpp */

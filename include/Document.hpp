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
		/**
		 
		 */
		Document(const std::string& title);
		
		/**
		 
		 */
		
		virtual ~Document() = default;
		
		/**
		 
		 */
		void addPage(const std::shared_ptr<Page>& p);
		
		/**
		 
		 */
		virtual std::ostream& write(std::ostream& out) const;
		
		/**
		 
		 */
		friend std::ostream& operator << (std::ostream &out, const PDF_Plus::Document &d);

		/**
		 Cross reference table of this Document
		 */
		std::weak_ptr<Xref> xref() const;
		
		/**
		 Cross reference table of this Document,
		 operator for implicit conversion
		 */
		operator std::weak_ptr<Xref>();
		
	private:
		std::size_t _headerOffset = 0;
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

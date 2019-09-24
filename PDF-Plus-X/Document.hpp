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
		
	private:
		std::size_t _headerOffset = 0;
		Version _docVersion;
		std::shared_ptr<Catalog> _catalog;
		
		/**
		 Returns the PDF file header (with magic numbers)
		 */
		std::string generateHeader() const;
		
		/// MARK: Xref
		// XRef table impl.
		// TODO: Use weak_ptr!
		// TODO: Own class! So that Object doesnt need to know about 'Document' but the independent class Xref..!
		mutable std::vector<Object*> xrefList{};
		friend class Object;
		/**
		 
		 */
		void addObject(Object* obj) const;
		
		/**
		 
		 */
		void removeObject(Object* obj) const;
		
		/**
		 
		 */
		void writeXRef(std::ostream& out) const;
	};

}

#endif /* Document_hpp */

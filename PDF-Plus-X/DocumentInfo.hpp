//
//  DocumentInfo.hpp
//  PDF-Plus-X
//
//  Created by Mac ERPA on 27.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef DocumentInfo_hpp
#define DocumentInfo_hpp

#include <cstdio>
#include "Object.hpp"
#include "ObjectRef.hpp"

namespace PDF_Plus {
    class Document;
    /**
     Document Info (Metadata), See PDF-Reference Section 10.2.1 "Document Information Dictionary"
     */
    class DocumentInfo : public Object {
    public:
        /**
         
         */
        DocumentInfo(const std::weak_ptr<Xref>& parent, const std::string& title) : Object{parent}
        {
			(*this)["Title"] = String{title};
			(*this)["Author"] = String{"Doc-Author"};
			(*this)["Creator"] = String{"PDF-PLUS Lib"};
			(*this)["Producer"] = String{"PDF-PLUS Lib"};
        }
    };
}

#endif /* DocumentInfo_hpp */

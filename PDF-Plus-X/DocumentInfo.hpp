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

namespace PDF_Plus {
    class Document;
    /**
     Document Info (Metadata), See PDF-Reference Section 10.2.1 "Document Information Dictionary"
     */
    class DocumentInfo : public Object {
    public:
        /**
         
         */
        DocumentInfo(const Document* parent, const std::string& title) : Object{parent}
        {
            // TODO: Escape those strings ( Unbalanced Parenthesis! )
            (*this)["Title"] = "("+title+")";
            (*this)["Author"] = "(Doc-Author)";
            (*this)["Creator"] = "(PDF-PLUS Lib)";
            (*this)["Producer"] = "(PDF-PLUS Lib)";
        }
    };
}

#endif /* DocumentInfo_hpp */

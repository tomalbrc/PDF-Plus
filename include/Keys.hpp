//
//  Keys.h
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 29.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Keys_h
#define Keys_h

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)
#define STR_KEY(x) const std::string x = STR(x)

/**
 A place to store all possible keys for Dictionaries
 */
namespace PDF_Plus::Key {
	// General
	STR_KEY(Type);
	STR_KEY(Subtype);
	STR_KEY(Length);

	// Page(s)
	STR_KEY(MediaBox);
	STR_KEY(TrimBox);
	STR_KEY(CropBox);
	STR_KEY(Contents);
	STR_KEY(Resources);
	STR_KEY(Rotate);
	STR_KEY(Kids);
	STR_KEY(Parent);
	STR_KEY(Count);

	// Resources
	STR_KEY(Font);
	STR_KEY(XObject);
	
	// Font
	STR_KEY(BaseFont);
	
	// Stream
	STR_KEY(Filter);
}

#endif /* Keys_h */

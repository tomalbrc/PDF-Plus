//
//  Stream.hpp
//  PDF-Plus-X
//
//  Created by Tom Albrecht on 24.09.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#ifndef Stream_hpp
#define Stream_hpp

#include <cstdio>
#include "Object.hpp"

// TODO: StreamObject that writes out Object Header + Stream data?

namespace PDF_Plus {
	/**
	 TODO: Own class for the Stream and separate StreamObject as Container for it
	 */
	class Stream : public Object {
	public:
		/**
		 
		 */
		Stream(const Document* parent) : Object{parent}
		{
			
		}
		
		/**
		 
		 */
		virtual void write(std::ostream& out) const override
		{
			writeBegin(out);
			_dict.write(out);
			out << ">>" << '\n'; // Dict end
			out << "stream" << '\n'; // Stream begin
			out << streamData.str();
			out << "endstream" << '\n'; // stream end
			out << "endobj" << '\n'; // Object end
		}
		
		/**
		 
		 */
		void drawText(std::string text, int x, int y, int fontSize)
		{
			streamData << "BT";
			streamData << " /F1 " << fontSize << " Tf";
			streamData << " " << x << " " << y << " Td";
			streamData << " (" << text << ")Tj";
			streamData << " ET" << '\n';
			(*this)["Length"] = std::to_string(streamData.str().length());
		}
		
		/**
		 
		 */
		void drawLine(int x1, int y1, int x2, int y2)
		{
			streamData << x1 << " " << y1;
			// START: x y m
			// LINE TO: x y l
			// CURVE: x1 y1 x2 y2 v
			// RECT: x1 y1 x2 y2 re
			// h = close path
			// S = stroke path
			streamData << " m " << x2 << " " << y2 << " l h S" << '\n';
		}
		
		/**
		 
		 */
		void drawRect(int x1, int y1, int x2, int y2)
		{
			streamData << x1 << " " << y1 << " " << x2 << " " << y2 << " re S" << '\n';
		}
		
	private:
		std::stringstream streamData;
	};

}

#endif /* Stream_hpp */

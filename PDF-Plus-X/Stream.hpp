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
#include <zlib.h>
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
			(*this)["Filter"] = "/FlateDecode";
		}
		
		/**
		 
		 */
		virtual void write(std::ostream& out) const override
		{
			auto data = this->compressData(this->streamData);
			
			// FIXME: This sucks
			writeBegin(out);
			out << "/Length " << data.size() << " /Filter " << "/FlateDecode";
			out << ">>" << '\n'; // Dict end
			out << "stream" << '\n'; // Stream begin
			
			for (const auto& b: data)
				out << (char)b;
			out << '\n';
			out << "endstream" << '\n'; // stream end
			out << "endobj" << '\n'; // Object end
		}
		
		/**
		 
		 */
		void drawText(std::string text, int x, int y, int fontSize)
		{
			std::stringstream streamData;
			streamData << "BT";
			streamData << " /F1 " << fontSize << " Tf";
			streamData << " " << x << " " << y << " Td";
			streamData << " (" << text << ")Tj";
			streamData << " ET" << '\n';
			
			auto str = streamData.str();
			std::copy((std::byte*)str.data(),
					  (std::byte*)str.data()+str.length(),
					  std::back_inserter(this->streamData));
		}
		
		/**
		 
		 */
		void drawLine(int x1, int y1, int x2, int y2)
		{
			std::stringstream streamData;

			streamData << x1 << " " << y1;
			// START: x y m
			// LINE TO: x y l
			// CURVE: x1 y1 x2 y2 v
			// RECT: x1 y1 x2 y2 re
			// h = close path
			// S = stroke path
			streamData << " m " << x2 << " " << y2 << " l h S" << '\n';
		
			auto str = streamData.str();
			std::copy((std::byte*)str.data(),
					  (std::byte*)str.data()+str.length(),
					  std::back_inserter(this->streamData));
		}
		
		/**
		 
		 */
		void drawRect(int x1, int y1, int x2, int y2)
		{
			std::stringstream streamData;
			streamData << x1 << " " << y1 << " " << x2 << " " << y2 << " re S" << '\n';
			
			auto str = streamData.str();
			std::copy((std::byte*)str.data(),
					  (std::byte*)str.data()+str.length(),
					  std::back_inserter(this->streamData));
		}
		
	private:
		std::vector<std::byte> streamData;
		
		std::vector<std::byte> compressData(const std::vector<std::byte>& data) const
		{
			static_assert(sizeof(Bytef) == sizeof(std::byte), "Bytef != std::byte");
			
			auto blen = data.size()*2;
			auto buffer = new std::byte[blen];
			compress((Bytef*)buffer, &blen, (Bytef*)data.data(), data.size()+1);
			return std::vector<std::byte>{buffer, buffer+blen};
		}
	};

}

#endif /* Stream_hpp */

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
#include <regex>
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
        
        virtual std::size_t size() const override
        {
            std::stringstream s;
            auto o = *this;
            o.write(s);
            return s.str().length();
        }
		
		/**
		 
		 */
		virtual void write(std::ostream& out) override
		{
			auto data = this->compressData(this->streamData);
            _dict[Key::LengthKey] = std::to_string(data.size()+1);
            
			writeBegin(out);
			{
				_dict.write(out);
				out << "stream" << '\n'; // Stream begin
				
				for (const auto& c: data)
					out << (const unsigned char)c;
				
				out << '\n';
				out << "endstream" << '\n'; // stream end
			}
			writeEnd(out);
		}
		
		/**
		 
		 */
		void drawText(std::string text, int x, int y, int fontSize)
		{
			text = escape(text);
			
			std::stringstream streamData;
			streamData << "BT";
			streamData << " /F1 " << fontSize << " Tf";
			streamData << " " << x << " " << y << " Td";
			streamData << " (" << text << ")Tj";
			streamData << " ET" << '\n';
			
			read(streamData.str());
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
		
			read(streamData.str());
		}
		
		/**
		 
		 */
		void drawRect(int x1, int y1, int x2, int y2)
		{
			std::stringstream streamData;
			streamData << x1 << " " << y1 << " " << x2 << " " << y2 << " re S" << '\n';
			read(streamData.str());
		}
		
	private:
		std::vector<std::byte> streamData;
		
		std::vector<std::byte> compressData(const std::vector<std::byte>& data) const
		{
			static_assert(sizeof(Bytef) == sizeof(std::byte), "Bytef != std::byte");
			
			auto blen = data.size()*2;
			auto buffer = new std::byte[blen]();
			compress(reinterpret_cast<Bytef*>(buffer),
					 &blen,
					 reinterpret_cast<const Bytef*>(data.data()),
					 data.size());
			
			std::vector<std::byte> res{buffer, buffer+blen};
			
			delete[] buffer;
			
			return res;
		}
		
		std::string& escape(std::string& text) const
		{
			text = std::regex_replace(text, std::regex(R"(\\)"), R"(\\)");
			text = std::regex_replace(text, std::regex(R"(\()"), R"(\()");
			text = std::regex_replace(text, std::regex(R"(\))"), R"(\))");
			return text;
		}
		
		void read(const std::string& str)
		{
			std::copy(reinterpret_cast<const std::byte*>(str.data()),
					  reinterpret_cast<const std::byte*>(str.data()+str.length()),
					  std::back_inserter(this->streamData));
			
		}
	};

}

#endif /* Stream_hpp */

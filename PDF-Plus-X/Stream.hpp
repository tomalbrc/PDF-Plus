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
	 Object with Dict and additional stream data (libz compressed)
	 See PDF Reference Section #.#.#
	 */
	class Stream : public Object {
	public:
		/**
		 
		 */
		Stream(const std::weak_ptr<Xref>& parent) : Object{parent}
		{
			_dict["Filter"] = "/FlateDecode";
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
		virtual std::ostream& write(std::ostream& out) override
		{
			auto data = this->compressData(this->streamData);
            _dict[Key::Length] = data.size()+1;
            
			writeBegin(out);
			{
				_dict.write(out);
				out << NL << "stream"; // Stream begin
				
				for (const auto& c: data)
					out << static_cast<const unsigned char>(c);
				
				out << NL << "endstream"; // stream end
			}
			writeEnd(out);
			
			return out;
		}
		
		/**
		 
		 */
		void drawText(std::string text, int x, int y, int fontSize)
		{
			text = escape(text);
			
			std::stringstream streamData;
			streamData << NL << "BT";
			streamData << " /F1 " << fontSize << " Tf";
			streamData << " " << x << " " << y << " Td";
			streamData << " (" << text << ")Tj";
			streamData << " ET";
			
			read(streamData.str());
		}
		
		/**
		 
		 */
		void drawLine(int x1, int y1, int x2, int y2)
		{
			std::stringstream streamData;

			streamData << NL << x1 << " " << y1;
			// START: x y m
			// LINE TO: x y l
			// CURVE: x1 y1 x2 y2 v
			// RECT: x1 y1 x2 y2 re
			// h = close path
			// S = stroke path
			streamData << " m " << x2 << " " << y2 << " l h S";
		
			read(streamData.str());
		}
		
		/**
		 
		 */
		void drawRect(int x1, int y1, int x2, int y2)
		{
			std::stringstream streamData;
			streamData << NL << x1 << " " << y1 << " " << x2 << " " << y2 << " re S";
			read(streamData.str());
		}
		
	private:
		std::vector<std::byte> streamData;
		
		std::vector<std::byte> compressData(const std::vector<std::byte>& data)
		{
			static_assert(sizeof(Bytef) == sizeof(std::byte), "Bytef != std::byte");
			
			uLongf blen = data.size()*2;
			auto buffer = new std::byte[blen]();
			compress(reinterpret_cast<Bytef*>(buffer),
					 &blen,
					 reinterpret_cast<const Bytef*>(data.data()),
					 static_cast<uLongf>(data.size()));
			
			std::vector<std::byte> res{buffer, buffer+blen};
			
			delete[] buffer;
			
			res.insert(res.begin(), std::byte{'\n'});
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

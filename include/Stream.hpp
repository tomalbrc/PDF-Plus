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
#include "Types.hpp"

// TODO: StreamObject that writes out Object Header + Stream data?

namespace PDF_Plus {
	class Image;
	class Font;

	/**
	 Object with Dict and additional stream data (libz compressed)
	 See PDF Reference Section #.#.#
	 */
	class Stream : public Object {
	public:
		/**
		 
		 */
		Stream(const std::weak_ptr<Xref>& parent);
        
		virtual std::size_t size() const override;
		
		/**
		 
		 */
		virtual std::ostream& write(std::ostream& out) override;
		
		/**
		 
		 */
		void drawText(std::string text, const std::weak_ptr<Font>& font, Point p);
		
		/**
		 
		 */
		void drawLine(Point p1, Point p2);
		
		/**
		 
		 */
		void drawRect(Rect r);
		
		/**
		 
		 */
		void drawImage(const std::weak_ptr<Image>& image);
		
	protected:
		std::vector<std::byte> streamData;
		
		std::vector<std::byte> compressData(const std::vector<std::byte>& data);
		
		std::string& escape(std::string& text) const;
		
		void read(const std::string& str);
	};

}

#endif /* Stream_hpp */

//
//  Stream.cpp
//  PDF-Plus-macOS
//
//  Created by Tom Albrecht on 02.10.19.
//  Copyright © 2019 Tom Albrecht. All rights reserved.
//

#include "Stream.hpp"

#include "Image.hpp"
#include "Font.hpp"

namespace PDF_Plus {

	Stream::Stream(const std::weak_ptr<Xref>& parent) : Object{parent}
	{
		_dict[Key::Filter] = "/FlateDecode";
	}
	
	std::size_t Stream::size() const
	{
		std::stringstream s;
		auto o = *this;
		o.write(s);
		return s.str().length();
	}
	
	/**
	
	 */
	std::ostream& Stream::write(std::ostream& out)
	{
		auto data = this->compressData(this->streamData);
		_dict[Key::Length] = uint64_t{data.size()};
	
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
	void Stream::drawText(std::string text, const std::weak_ptr<Font>& font, Point p)
	{
		text = escape(text);
	
		std::stringstream streamData;
		streamData << NL << "BT";
		streamData << " /" << font.lock()->resourceName() << " " << font.lock()->properties().fontSize << " Tf";
		streamData << " " << p.x << " " << p.y << " Td";
		streamData << " (" << text << ")Tj";
		streamData << " ET";
		
		read(streamData.str());
	}
	
	/**
	
	 */
	void Stream::drawLine(Point p1, Point p2)
	{
		std::stringstream streamData;
	
		streamData << NL << p1.x << " " << p1.y;
		// START: x y m
		// LINE TO: x y l
		// CURVE: x1 y1 x2 y2 v
		// RECT: x1 y1 x2 y2 re
		// h = close path
		// S = stroke path
		streamData << " m " << p2.x << " " << p2.y << " l h S";
	
		read(streamData.str());
	}
	
	/**
	
	 */
	void Stream::drawRect(Rect r)
	{
		std::stringstream streamData;
		streamData << NL << r.origin.x << " " << r.origin.y << " " << r.size.width << " " << r.size.height << " 	re S";
		read(streamData.str());
	}
	
	void Stream::drawImage(const std::weak_ptr<Image>& image) {
		std::stringstream streamData;
		streamData << NL << "q 132 0 0 132 45 140 cm " << "/" << image.lock()->imageInfo().name << " Do Q";
		read(streamData.str()); // Translate 45,140, Scale by 132
	}
	
	/// MARK: Private
	
	std::vector<std::byte> Stream::compressData(const std::vector<std::byte>& data)
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
	
	std::string& Stream::escape(std::string& text) const
	{
		text = std::regex_replace(text, std::regex(R"(\\)"), R"(\\)");
		text = std::regex_replace(text, std::regex(R"(\()"), R"(\()");
		text = std::regex_replace(text, std::regex(R"(\))"), R"(\))");
		return text;
	}
	
	void Stream::read(const std::string& str)
	{
		std::copy(reinterpret_cast<const std::byte*>(str.data()),
				  reinterpret_cast<const std::byte*>(str.data()+str.length()),
				  std::back_inserter(this->streamData));
	}
}

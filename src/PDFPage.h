#pragma once

#include "PDFObject.h"

namespace minipdf
{
class Page : public minipdf::Object
{
public:
	std::string type = "Page";
	const minipdf::Pages* parent() const
	{
		
	}

	virtual void write(std::iostream& dest) const override
	{
		minipdf::Object::writeHead(dest);
		minipdf::Object::writeProperties(dest);
		minipdf::Object::writeTail(dest);
	}
};
} // namespace minipdf

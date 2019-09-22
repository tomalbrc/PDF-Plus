#pragma once

#include "PDFObject.h"
#include "PDFPages.h"

namespace minipdf
{
class Catalog : public minipdf::Object
{
public:
	std::string type = "Catalog";
	minipdf::Pages *pages;

	virtual void write(std::iostream& dest) const override
	{
		minipdf::Object::writeHead(dest);
		minipdf::Object::writeProperties(dest);
		minipdf::Object::writeTail(dest);
	}
};
} // namespace minipdf

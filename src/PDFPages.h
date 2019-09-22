#pragma once

#include "PDFObject.h"
#include "PDFPage.h"

namespace minipdf
{
class Pages : public minipdf::Object
{
public:
	std::string type = "Pages";
	
	void addPage(Page* p)
	{
		p->parent(this);
		kids.emplace_back(p);
	}
	
	const std::vector<minipdf::Page*>& pages() const
	{
		return kids;
	}
	

	virtual void write(std::iostream& dest) const override
	{
		minipdf::Object::writeHead(dest);
		minipdf::Object::writeProperties(dest);
		dest << "/Count " << kids.size();
		dest << "/Kids " << minipdf::writeArray(kids);
		minipdf::Object::writeTail(dest);
	}
	
private:
	std::vector<minipdf::Page*> kids;
};
} // namespace minipdf

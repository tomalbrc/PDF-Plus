#pragma once

#include "PDFObject.h"

namespace minipdf
{
class XRef : public minipdf::Object
{
public:

	void add(Object&& obj)
	{
		obj.number = _objects.size()+1;
		_objects.emplace_back(std::move(obj));
	}

	std::vector<Object> objects() const
	{
		return _objects;
	}

	virtual void write(std::iostream& dest) const override
	{
		dest << "xref" << kNewline;
		dest << "0 " << objects().size()+1 << kNewline;
		dest << "trailer" << kNewline;
		dest << "<<" << kNewline;
		dest << "/Size " << objects().size()+1 << kNewline;
		dest << "/Root 1 0 R" << kNewline;
		dest << ">>" << kNewline;
		dest << "startxref" << kNewline;
		return;
	}
	
private:
	std::vector<Object> _objects;

};
} // namespace minipdf

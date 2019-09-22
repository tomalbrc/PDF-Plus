#pragma once

#include "PDFObject.h"
#include "PDFXRef.h"

namespace minipdf
{
class Document : public minipdf::Object
{
public:
	float version = 1.7;
	
	void add(Object&& obj) {
		xr.add(std::move(obj));
	}
	
	const std::vector<Object> objects() const
	{
		return xr.objects();
	}

	XRef xr;

	virtual void write(std::iostream& dest) const override
	{
		dest << "%PDF-" << std::fixed << std::setprecision(1) << version << kNewline;
		for (const auto& child : objects())
		{
			child.write(dest);
		}
		xr.write(dest);
		dest << "%%EOL" << kNewline;
		return;
	}
};
} // namespace minipdf

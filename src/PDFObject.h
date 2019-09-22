#pragma once

#include "Base.h"
static auto kNewline = '\n';

namespace minipdf
{
	template <class T>
	std::string writeArray(const std::vector<T*>& range)
	{
		std::stringstream dest{"[ "};
		for (const auto& item: range)
		{
				std::string j = *item;
				dest << j << " ";
		}
		dest << "]";
		return dest.str();
	}


class Object;
class Object
{
public:
	uint32_t number;
	std::map<std::string, std::string> properties;
	std::string type;

	virtual void write(std::iostream& dest) const
	{
		writeHead(dest);
		writeProperties(dest);
		writeTail(dest);
	}
	
	std::vector<Object> children;


	operator std::string() const {
		return std::to_string(number) + " 0 R";
	}

protected:
	virtual void writeHead(std::iostream& dest) const
	{
		dest << number << " 0 obj " << kNewline;
		dest << "<< " << kNewline;
		dest << "/Type /" << type << kNewline;
	}
	
	virtual void writeProperties(std::iostream& dest) const
	{
		for (const auto& kvpair : properties)
		{
			dest << kvpair.first << " " << kvpair.second << kNewline;
		}
	}
	
	virtual void writeTail(std::iostream& dest) const
	{
		dest << ">> " << kNewline;
		dest << "endobj " << kNewline;
	}
};

} // namespace minipdf

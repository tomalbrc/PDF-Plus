
#include "Base.h"

#include <sstream>
#include <cassert>

class InputParser{
    public:
        InputParser (int &argc, char **argv){
            for (int i=1; i < argc; ++i)
                this->tokens.push_back(std::string(argv[i]));
        }
        /// @author iain
        const std::string& getCmdOption(const std::string &option) const{
            std::vector<std::string>::const_iterator itr;
            itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()){
                return *itr;
            }
            static const std::string empty_string("");
            return empty_string;
        }
        /// @author iain
        bool cmdOptionExists(const std::string &option) const{
            return std::find(this->tokens.begin(), this->tokens.end(), option)
                   != this->tokens.end();
        }
    private:
        std::vector <std::string> tokens;
};

int main(int argc, char** argv)
{
	using namespace minipdf;
	
	Document doc;
	
	InputParser p{argc, argv};
	if (p.cmdOptionExists("-v")) {
		const auto v = p.getCmdOption("-v");
		doc.version = std::stof(v);
	}
	
	Catalog cata;
	Pages pgs;
	Page p;
	
	
	Object oo1;
	oo1.type = "Catalog";
	oo1.properties["/Extensions"] = "<</ADBE   <</BaseVersion /1.7 /ExtensionLevel 3   >>   >>";
	oo1.properties["/Pages"] = "2 0 R";
	
	Object oo2;
	oo2.type = "Pages";
	oo2.properties["/Count"] = "1";
	oo2.properties["/Kids"] = "[3 0 R]";
	
	Object oo3;
	oo3.type = "Page";
	oo3.properties["/Parent"] = "2 0 R";
	oo3.properties["/MediaBox"] = "[0 0 612 792]";
	//oo3.properties["/Content"] = "0";
	
	doc.add(std::move(oo1));
	doc.add(std::move(oo2));
	doc.add(std::move(oo3));
	
	std::stringstream ss;
	doc.write(ss);
	
	std::cout << ss.str() << std::endl;
	return 0;
}

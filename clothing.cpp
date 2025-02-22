#include "clothing.h"
#include <iomanip>
#include <sstream>

using namespace std;

std::set<std::string> Clothing::keywords() const {
	set<string> keywords;

	keywords = parseStringToWords(convToLower(brand_));

	set<string> name_keywords;
	name_keywords = parseStringToWords(name_);

	keywords = setUnion(keywords, name_keywords);

	return keywords;
}

std::string Clothing::displayString() const {
	
	ostringstream oss;
	oss << fixed << setprecision(2) << price_ ;

	return name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + oss.str() + " " + to_string(qty_) + " left." + "\n";
}

void Clothing::dump(std::ostream& os) const {
	os << "clothing\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << "\n";
}
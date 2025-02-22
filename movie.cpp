#include "movie.h"
#include <iomanip>
#include <sstream>

using namespace std;

std::set<std::string> Movie::keywords() const {
	set<string> keywords;
	keywords.insert(convToLower(genre_));

	set<string> name_keywords;
	name_keywords = parseStringToWords(name_);

	keywords = setUnion(keywords, name_keywords);

	return keywords;
}

std::string Movie::displayString() const {
	
	ostringstream oss;
	oss << fixed << setprecision(2) << price_ ;

	return name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + oss.str() + " " + to_string(qty_) + " left." + "\n";
}

void Movie::dump(std::ostream& os) const {
	os << "movie\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << "\n";
}
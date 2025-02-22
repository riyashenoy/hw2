#include "book.h"
#include <iomanip>
#include <sstream>

using namespace std;

std::set<std::string> Book::keywords() const {
	set<string> keywords;
	keywords = parseStringToWords(author_);
	keywords.insert(ISBN_);

	set<string> name_keywords;
	name_keywords = parseStringToWords(name_);

	keywords = setUnion(keywords, name_keywords);

	/* testing
	for (std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
        std::cout << *it << std::endl; 
    }
	*/


	return keywords;

}

std::string Book::displayString() const {
	ostringstream oss;
	oss << fixed << setprecision(2) << price_ ;

	return name_ + "\nAuthor: " + author_ + " ISBN: " + ISBN_ + "\n" + oss.str() + " " + to_string(qty_) + " left." + "\n";
}

void Book::dump(std::ostream& os) const {
	os << "book\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << author_ << "\n";
}
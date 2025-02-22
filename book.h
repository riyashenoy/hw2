#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include "product.h"
#include "util.h"


class Book : public Product {
public:
	Book(const std::string& category, const std::string& name, double price, int qty, const std::string& author, const std::string& isbn)
		: Product(category, name, price, qty), ISBN_(isbn), author_(author) {}

	std::set<std::string> keywords() const override;
	std::string displayString() const override;
	void dump(std::ostream& os) const override;


private:
	std::string ISBN_;
	std::string author_;
};


#endif
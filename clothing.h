#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include "product.h"
#include "util.h"

class Clothing : public Product {
public:
	Clothing(const std::string& category, const std::string& name, double price, int qty, const std::string& size, const std::string& brand)
		: Product(category, name, price, qty), size_(size), brand_(brand) {}

	std::set<std::string> keywords() const override;
	std::string displayString() const override;
	void dump(std::ostream& os) const override;


private:
	std::string size_;
	std::string brand_;
};


#endif
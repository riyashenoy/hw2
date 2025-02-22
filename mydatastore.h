#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "user.h"
#include "util.h"
#include <set>
#include <queue>

class MyDataStore : public DataStore {
public:
    MyDataStore() {

    }
    ~MyDataStore() {
        for(Product* p : products_){
            delete p;
        }

        for(auto& userPair : users_){
            delete userPair.second; 
        }
    }

    void addProduct(Product* p) override {
        products_.push_back(p);

        std::set<std::string> keywords = p->keywords();

        set<string>::iterator itr;
        for (itr = keywords.begin(); itr != keywords.end(); itr++) {
            keywordList_[*itr].insert(p);
        }
    }

    void addUser(User* u) override {
        users_.insert({ u->getName(), u });
    }

    std::vector<Product*> search(std::vector<std::string>& terms, int type) override {
        /*  testing cout << terms[0] << endl; */
        std::vector<Product*> resultingProducts;
        set<Product*> products;
        set<Product*> productList;
        bool firstFind = true;
       
        if (type == 0) {
            for (size_t i = 0; i < terms.size(); i++) {
                if (keywordList_.find(terms[i]) != keywordList_.end()) {
                    products = keywordList_[terms[i]];
                    if (firstFind) {
                        productList = products;
                        firstFind = false;
                    }
                    productList = setIntersection(productList, products);

                }
                else {
                    return resultingProducts;
                }
            }
            set<Product*>::iterator itr;
            for (itr = productList.begin(); itr != productList.end(); itr++) {
                resultingProducts.push_back(*itr);
            }
        }
        else if (type == 1) {
            for (size_t i = 0; i < terms.size(); i++) {
                if (keywordList_.find(terms[i]) != keywordList_.end()) {
                    products = keywordList_[terms[i]];
                    set<Product*>::iterator itr;

                    for (itr = products.begin(); itr != products.end(); itr++) {
                        if (count(resultingProducts.begin(), resultingProducts.end(), *itr) == 0) {
                            resultingProducts.push_back(*itr);
                        }
                    }
                }
            }
        }
        return resultingProducts;
    }

    void dump(std::ostream& ofile) override {
        for (size_t i = 0; i < products_.size(); i++) {
            products_[i]->dump(ofile);
        }

        map<string, User*>::iterator it;
        for (it = users_.begin(); it != users_.end(); it++) {
            it->second->dump(ofile);
        }
    }

    void addToCart(const std::string& username, int index, const std::vector<Product*>& hits) {

        if (users_.find(username) != users_.end() || index < 1) {
            Product* product = hits[index - 1];
            carts_[username].push(product);
        }
        else {
            cout << "Invalid request" << endl;
        }
    }

    void viewCart(const std::string& username) {
        if (users_.find(username) != users_.end()) {
            queue<Product*> cart = carts_[username];
            
            int itemCount = 0;

            while(!cart.empty()) {
                Product* front = cart.front();

                itemCount++;
                cout << "Item " << itemCount << endl;

                cout << front->displayString();
                cart.pop();
            }
        }
        else {
            cout << "Invalid username" << endl;
        }

    }


    void buyCart(const std::string& username) {
        queue<Product*> remainingCart;
        if (users_.find(username) != users_.end()) {
            queue<Product*> cart = carts_[username];
            User* user = users_[username];
            while (!cart.empty()) {
                Product* front = cart.front();
                if (front->getQty() >= 1 && user->getBalance() >= front->getPrice()) {
                    
                    user->deductAmount(front->getPrice());
                    front->subtractQty(1);
                    cart.pop();
                }
                else {
                    remainingCart.push(cart.front());
                    cart.pop();
                }
            }
            carts_[username] = remainingCart;
        }
        else {
            cout << "Invalid username" << endl;
        }
    }
    void save(const std::string& filename) {

        std::ofstream ofile(filename.c_str());
        if (!ofile) {
            std::cerr << "file wont open! testing" << filename << std::endl;
            return;
        }

        ofile << "<products>\n";
        ofile << fixed << setprecision(2);

        for (size_t i = 0; i < products_.size(); i++) {
            products_[i]->dump(ofile);
        }
        ofile << "</products>\n";

        ofile << "<users>\n";

        for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
            ofile << setprecision(2);
            it->second->dump(ofile);
        }

        ofile << "</users>\n";
     }

private:
    vector<Product*> products_;
    map<string, User*> users_;
    map<string, queue<Product*>> carts_;
    map<string, set<Product*>> keywordList_;
};

#endif
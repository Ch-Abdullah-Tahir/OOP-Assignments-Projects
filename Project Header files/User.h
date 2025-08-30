#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "Cart.h"
#include "Order.h"
#include "Product.h"
#include "Exceptions.h"
#include "File Manager.h"

using namespace std;
//const string RESET = "\033[0m";
//const string GREEN = "\033[32m";
//const string YELLOW = "\033[33m";
extern const string RESET;
extern const string GREEN;
extern const string YELLOW;
class User {
public:
    string user_name;
    string password;
    string role;
    static int userCount;

    User() : user_name(""), password(""), role("") {}
    User(string uname, string pass) : user_name(uname), password(pass), role("") {}
    virtual ~User() {}
    virtual void userMenu() = 0;
};

int User::userCount = 0;

class Admin : public User {
public:
    Admin() { role = "admin"; }
    Admin(string uname, string pass) : User(uname, pass) { role = "admin"; }

    void userMenu() override {
        cout << "\t\t\t\t\t\t'Admin Menu'\n\t\t\t\t\t1) View Reports    2) Approve Product\n\t\t\t\t\t\t\t3) Exit\nChoice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "open the files for viewing" << endl;
        }
        else if (choice == 2) {
            cout << "approved";
        }
        else {
            cout << "Exiting Admin Menu\n";
        }
    }
};

class Buyer : public User {
    cart<Product> c;
    order* o[8];
    int products_in_1_order_count = 0;
    const int cartLimit = 10;
    int orderCount = 0;

public:
    Buyer() : User() {
        role = "buyer";
        for (int i = 0; i < 8; ++i) o[i] = nullptr;
    }
    Buyer(string u, string p) : User(u, p) {
        role = "buyer";
        for (int i = 0; i < 8; ++i) o[i] = nullptr;
    }

    void Search_Products();
    void Add_to_cart();
    void place_order_via_cart();
    void View_Orders();
    void View_cart();
    void userMenu() override;

    int get_order_count() const { return orderCount; }
    order** get_o() { return o; }
    cart<Product>& get_cart() { return c; }

    ~Buyer() {
        for (int i = 0; i < orderCount; i++) {
            delete o[i];
            o[i] = nullptr;
        }
    }

    friend class Seller;
    friend class Authentication;
};

class Seller : public User {
public:
    Product* p[12];
    int productcount;
public:
    void View_Order(User* users[], const string roles[], int userCount)
    {
        bool foundOrder = false;

        for (int i = 0; i < userCount; i++) {
            if (roles[i] == "buyer") {
                Buyer* buyer = dynamic_cast<Buyer*>(users[i]);
                if (!buyer) continue;

                int orderCount = buyer->get_order_count();
                order** orders = buyer->get_o();

                for (int j = 0; j < orderCount; j++) {
                    order* o = orders[j];
                    if (!o) continue;

                    bool containsSellerProduct = false;

                    for (int k = 0; k < o->product_count; k++) {
                        Product* p = o->prod[k];
                        if (p && to_string(p->Sellerid) == this->user_name) {
                            containsSellerProduct = true;
                            break;
                        }
                    }

                    if (containsSellerProduct) {
                        foundOrder = true;
                        std::cout << "\nOrder from Buyer = " << buyer->user_name << "\n";
                        o->display_order();



                    }
                }
            }
        }

        if (!foundOrder) {
            std::cout << "No orders found for this seller.\n";
        }
    }

    Seller() : User() {
        role = "seller";
        productcount = 0;
        for (int i = 0; i < 12; ++i) p[i] = nullptr;
    }
    Seller(string uname, string pass) : User(uname, pass) {
        role = "seller";
        productcount = 0;
        for (int i = 0; i < 12; ++i) p[i] = nullptr;
    }

    void Add_Product();
    void Update_Product();
    void Delete_Product();

    void userMenu() override;

    ~Seller() {
        for (int i = 0; i < productcount; ++i) {
            delete p[i];
            p[i] = nullptr;
        }
    }

    friend class Authentication;
};




void Buyer::Search_Products() {
    ifstream fin("product.txt");
    if (!fin) {
        cout << "Failed to open product.txt\n";
        return;
    }

    bool found = false;
    while (!fin.eof()) {
        string pid, name, cat;
        double price;
        int qty;
        string sid;
        fin >> pid;
        if (fin.fail()) break;
        fin >> name >> cat >> price >> qty >> sid;
        if (fin.fail()) break;
        found = true;
        cout << "\nPRODUCT ID   = " << pid
            << "\nNAME         = " << name
            << "\nCATEGORY     = " << cat
            << "\nPRICE        = " << price
            << "\nSTOCK        = " << qty
            << "\nSELLER       = " << sid << endl;
    }
    fin.close();
    if (!found) cout << "No Products Found\n";
}

void Buyer::Add_to_cart() {
    ifstream fin("product.txt");
    if (!fin) {
        cout << "Failed to open product.txt\n";
        return;
    }

    int pid, sid, name, cat;
    double price;
    int qty;

    cout << "Enter Product ID: ";
    int t_pid; cin >> t_pid;
    cout << "Enter Seller ID: ";
    int t_sid; cin >> t_sid;

    bool found = false;
    while (fin >> pid >> name >> cat >> price >> qty >> sid) {
        if (pid == t_pid && sid == t_sid) {
            Product* np = new Product();
            np->ProductID = pid;
            np->ProductName = name;
            np->ProductCategory = cat;
            np->ProductPrice = price;
            np->ProductQuantity = qty;
            np->Sellerid = sid;
            c += np;
            cout << "Product added to cart.\n";
            found = true;
            break;
        }
    }
    fin.close();
    if (!found) cout << "Product not found\n";
}

void Buyer::place_order_via_cart() {
    if (orderCount >= 8) {
        cout << "Maximum order limit reached.\n";
        return;
    }
    if (c.Items_Added == 0) {
        cout << "Cart empty, cannot place order.\n";
        return;
    }

    o[orderCount] = new order();

    for (int i = 0; i < c.Items_Added; i++) {
        Product* prod = c.p[i];
        if (prod) o[orderCount]->add_product(prod);
    }
    o[orderCount]->setdetails();
    orderCount++;

    c.clear();
    products_in_1_order_count = 0;

    cout << "Order placed successfully.\n";
}

void Buyer::View_Orders() {
    if (orderCount == 0) {
        cout << "No orders placed yet.\n";
        return;
    }
    for (int i = 0; i < orderCount; i++) {
        if (o[i]) {
            cout << "\nOrder #" << i + 1 << " details:\n";
            o[i]->display_order();
        }
    }
}

void Buyer::View_cart() {
    if (c.Items_Added == 0) {
        cout << "Cart is empty.\n";
        return;
    }
    cout << "Cart Contents:\n";
    for (int i = 0; i < c.Items_Added; i++) {
        c.p[i]->displayDetails();
    }
}

void Buyer::userMenu() {
    cout << "====================================================================================================\n";
    cout << "||                                         (Buyer Menu)										   ||\n";
    cout << "||1) Search Products\t\t\t2) Add to Cart\n3) Place Order\t\t\t4) View Orders\n\t\t\t5) View Cart\n||";
    cout << "====================================================================================================\n";
    int choice; cin >> choice;
    switch (choice) {
    case 1:
        Search_Products();
        break;
    case 2:
        Add_to_cart();
        break;
    case 3:
        place_order_via_cart();
        break;
    case 4:
        View_Orders();
        break;
    case 5:
        View_cart();
        break;
    default:
        cout << "Invalid choice!\n";
    }
}



void Seller::Add_Product() {
    if (productcount >= 12) {
        cout << "Product limit reached.\n";
        return;
    }

    cout << "Enter product category (E/B/C): ";
    char c; cin >> c;
    Product* newProd = nullptr;
    switch (c) {
    case 'E': newProd = new ElectronicsProduct(); newProd->setcateg("Electronics"); break;
    case 'B': newProd = new BookProduct(); newProd->setcateg("Book"); break;
    case 'C': newProd = new ClothingProduct(); newProd->setcateg("Clothing"); break;
    default:
        cout << "Invalid category entered.\n";
        return;
    }

    newProd->add();
    p[productcount++] = newProd;

    ofstream fout("product.txt", ios::app);
    if (fout) {
        fout << newProd->ProductID << " "
            << newProd->ProductName << " "
            << newProd->ProductCategory << " "
            << newProd->ProductPrice << " "
            << newProd->ProductQuantity << " "
            << newProd->Sellerid << "\n";
        fout.close();
        cout << "Product added successfully.\n";
    }
    else {
        cout << "Failed to open product.txt for writing.\n";
    }
}

void Seller::Update_Product() {
    cout << "Enter Product ID to update: ";
    int id; cin >> id;
    for (int i = 0; i < productcount; i++) {
        if (p[i] && p[i]->ProductID == id) {
            cout << "Enter new details = \n";
            p[i]->add();
            cout << "Product updated.\n";
            return;
        }
    }
    cout << "Product not found.\n";
}

void Seller::Delete_Product() {
    cout << "Enter Product ID to delete = ";
    int id; cin >> id;
    for (int i = 0; i < productcount; i++) {
        if (p[i] && p[i]->ProductID == id) {
            delete p[i];
            for (int j = i; j < productcount - 1; j++) p[j] = p[j + 1];
            p[productcount - 1] = nullptr;
            productcount--;
            cout << "Product deleted.\n";
            return;
        }
    }
    cout << "Product not found.\n";
}





void Seller::userMenu() {
    cout << "Seller Menu:\n";
    cout << "\t\t\t\t\1) Add Product\t\t\t\t2) Remove Product\n\t\t\t\t3) Update Product\t\t\t\t4) View Orders\nChoice: ";
    int ch; cin >> ch;
    switch (ch) {
    case 1: Add_Product(); break;
    case 2: Delete_Product(); break;
    case 3: Update_Product(); break;

    default: cout << "Invalid option\n"; break;
    }
}
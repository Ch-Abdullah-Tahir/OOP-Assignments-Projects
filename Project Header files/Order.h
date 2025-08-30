#pragma once
#include "Product.h"
#include <string>
#include <iostream>
using namespace std;

class order {
public:
    friend class Seller;
    int orderid;
    string shipping_status;
    int order_count;
    Product* prod[10];
    int product_count = 0;
    order() : orderid(0), shipping_status("pending"), order_count(0) {
        for (int i = 0; i < 10; i++) prod[i] = nullptr;
    }

    void add_product(Product* p) {
        if (order_count < 10) {
            prod[order_count++] = p;
        }
    }

    void setdetails() {
        cout << "Enter order id: ";
        cin >> orderid;
        cout << "Enter shipping status: ";


        cin >> shipping_status;
    }

    void display_order() {
        cout << "Order ID: " << orderid
            << "\nStatus: " << shipping_status << "\n";
        for (int i = 0; i < order_count; i++) {
            if (prod[i]) prod[i]->displayDetails();
        }
    }
};
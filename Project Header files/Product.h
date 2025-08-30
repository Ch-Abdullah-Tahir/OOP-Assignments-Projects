#pragma once
#include<string>
#include<iostream>
#include"File Manager.h"
#include<fstream>
using namespace std;
class FileManager;
class Product
{
public:
	int ProductID;
	string ProductName;
	string ProductCategory;
	string status = "pending";
	double ProductPrice;
	int ProductQuantity;
	int Sellerid;//sellerid is seller username+1-2 extra words (koi seller se login na marde)

	Product() : ProductID(0), ProductName(""), ProductCategory(""), ProductPrice(0), ProductQuantity(0), Sellerid(0) {}
	bool operator==(const Product& other) const {
		return this->ProductID == other.ProductID;
	}

	void add()
	{
		cout << "Enter Product ID\n";
		cin >> ProductID;
		cout << "Enter Product Name\n";
		cin >> ProductName;
		cout << "Enter product price\n";
		cin >> ProductPrice;
		cout << "Enter Product Quantity(Stock)\n";
		cin >> ProductQuantity;
		cout << "Enter Seller id,remember it because it should be same whenever you perform addition\n";
		cin >> Sellerid;
	}
	void setcateg(string c) {
		ProductCategory = c;
	}
	double get_product_price() {
		return ProductPrice;
	}

	virtual	void displayDetails() {
		cout << "ID: " << ProductID << "\nName: " << ProductName << "\nCategory: " << ProductCategory
			<< "\nPrice: " << ProductPrice << "\nQuantity: " << ProductQuantity
			<< "\nSeller ID: " << Sellerid << "\nStatus: " << status << endl;
	}

	virtual void ApplyDiscount() {
		cout << "Discount applied\n";
	}
	friend class FileManager;
	virtual ~Product() {}

};


class ElectronicsProduct : public Product {
public:
	void displayDetails() {
		Product::displayDetails();
	}
	void ApplyDiscount() {
		ProductPrice *= 0.9;
	}
	friend class FileManager;
};

class BookProduct : public Product {
public:
	void displayDetails() {
		Product::displayDetails();
	}
	void ApplyDiscount() {
		ProductPrice *= 0.8;
	}
	friend class FileManager;
};

class ClothingProduct : public Product {
public:
	void displayDetails() {
		Product::displayDetails();
	}
	void ApplyDiscount() {
		ProductPrice *= 0.85;
	}
	friend class FileManager;
};
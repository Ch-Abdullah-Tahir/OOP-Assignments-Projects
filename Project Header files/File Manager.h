#pragma once
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Product.h"
#include "Order.h"
#include "User.h"  

using namespace std;

class FileManager {
public:
	static void save_all(User* users[], string roles[], int userCount, Product products[], int productCount) {
		ofstream fout("users.txt");
		if (!fout) {
			cout << "Error opening users.txt\n";
			return;
		}
		for (int i = 0; i < userCount; i++) {
			if (users[i]) {
				fout << roles[i] << " "
					<< users[i]->user_name << " "
					<< users[i]->password << "\n";
			}
		}
		fout.close();

		ofstream pfout("products.txt");
		if (!pfout) {
			cout << "Error opening products.txt\n";
			return;
		}
		for (int i = 0; i < productCount; i++) {
			pfout << products[i].ProductID << " "
				<< products[i].ProductName << " "
				<< products[i].ProductCategory << " "
				<< products[i].ProductPrice << " "
				<< products[i].ProductQuantity << " "
				<< products[i].Sellerid << "\n";
		}
		pfout.close();
		cout << "ALL SAVED\n";
	}

	static void load_all(User* users[], string roles[], int& userCount, Product products[], int& productCount) {
		ifstream fin("users.txt");
		if (fin) {
			string role, uname, pass;
			int startIndex = userCount; // preserve any existing users like default Admin
			while (fin >> role >> uname >> pass) {
				string roleLower = role;
				transform(roleLower.begin(), roleLower.end(), roleLower.begin(), ::tolower);

				roles[startIndex] = roleLower;
				if (roleLower == "buyer") {
					users[startIndex] = new Buyer(uname, pass);
				}
				else if (roleLower == "seller") {
					users[startIndex] = new Seller(uname, pass);
				}
				else if (roleLower == "admin") {
					users[startIndex] = new Admin(uname, pass);
				}
				startIndex++;
			}
			userCount = startIndex;
			fin.close();
		}
		else {
			cout << "No users.txt found\n";
		}

		ifstream pfin("products.txt");
		if (pfin) {
			productCount = 0;
			while (pfin >> products[productCount].ProductID
				>> products[productCount].ProductName
				>> products[productCount].ProductCategory
				>> products[productCount].ProductPrice
				>> products[productCount].ProductQuantity
				>> products[productCount].Sellerid) {
				productCount++;
			}
			pfin.close();
		}
		else {
			cout << "No products.txt found\n";
		}

		cout << "ALL LOADED\n";
	}
};
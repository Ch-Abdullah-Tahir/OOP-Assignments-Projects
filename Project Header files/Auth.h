#pragma once
#include <iostream>
#include <string>
#include "Exceptions.h"  // Include custom exceptions
#include "File Manager.h"
#include "User.h"





using namespace std;
class Authentication {
public:
    void login(User* user[]) {
        cout << "Enter your user name = ";
        string name, pass;

        try {
            cin >> name;
            bool userFound = false;

            for (int i = 0; i < User::userCount; i++) {
                if (user[i]->user_name == name) {
                    userFound = true;
                    cout << "Enter your password = ";
                    cin >> pass;

                    if (user[i]->password == pass) {
                        cout << "Password matched, login successfully\n";
                        user[i]->userMenu();
                        return;
                    }
                    else {
                        throw InvalidLoginException("Password does not belong to the username try again");
                    }
                }
            }

            if (!userFound) {
                throw InvalidLoginException("INVALID USERNAME");
            }

        }
        catch (const InvalidLoginException& e) {
            cout << "Login Error        = " << e.what() << endl;
        }
        catch (...) {
            cout << "Unexpected error during login" << endl;
        }
    }

    void registerUser(User* users[], string roles[], int& count) {
        cout << "Select your role\n";
        cout << "Enter s for seller and b for buyer: ";
        char r;
        cin >> r;

        try {
            string name, pass;
            cout << "Enter your username: ";
            cin >> name;

            // Check if username already exists
            for (int i = 0; i < count; i++) {
                if (users[i] && users[i]->user_name == name) {
                    throw InvalidLoginException("Username already exists");
                }
            }

            cout << "Enter your password: ";
            cin >> pass;

            if (r == 's' || r == 'S') {
                users[count] = new Seller(name, pass);
                roles[count] = "seller";
                count++;
                User::userCount++;
                cout << "Seller account create successfull\n";
            }
            else if (r == 'b' || r == 'B') {
                users[count] = new Buyer(name, pass);
                roles[count] = "buyer";
                count++;
                User::userCount++;
                cout << "Buyer account create successfull\n";
            }
            else {
                throw InvalidUserRoleException(string(1, r));
            }

        }
        catch (const InvalidLoginException& e) {
            cout << "Registration Error: " << e.what() << endl;
        }
        catch (const InvalidUserRoleException& e) {
            cout << "Role Error: " << e.what() << endl;
        }
        catch (...) {
            cout << "Unexpected error during registration" << endl;
        }
    }
};
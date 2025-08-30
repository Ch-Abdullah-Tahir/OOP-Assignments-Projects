//Main

#include <iostream>
#include <conio.h>      

#include <algorithm>
#include <cctype>
#include <iomanip>
#include"File Manager.h"
#include <fstream>
#include"User.h"
#include"Auth.h"
#include"Product.h"

#include"Order.h"

const string GREEN = "\033[32m";
const string RESET = "\033[0m";
const string YELLOW = "\033[33m";
#define maxorders 5
Product products[128];
int product_count = 0;
using namespace std;

void Menu(int cursor) {
    system("cls");


    cout << YELLOW<< "|" << string(128, '=') << "|" << RESET << endl;
    cout << RESET << YELLOW << "|" << "\t||\t" << RESET<<setw(50) << GREEN<<"~( E-COMMERCE SYSTEM )~" << RESET<<YELLOW<< setw(46) << "    ||     |" << endl;
    cout << RESET << YELLOW << "|" << "\t||\t" << "                                                                                                          || \t |\n";
    cout << RESET << YELLOW << "|" << "\t||\t" << "                                                                                                          || \t |\n";
    cout << RESET << YELLOW << "|" << "\t||\t" << GREEN<<  "|######      |###### |###### |####|#### |####|#### |###### |######  |###### |######"<<RESET<<YELLOW<< "                       || \t | \n";
    cout << RESET << YELLOW << "|" << "\t||\t" << GREEN << "|##          |##     |## |## |##|###|## |##|###|## |##     |## |##  |##     |##        " << RESET << YELLOW << "                   || \t |\n";
    cout << RESET << YELLOW << "|" << "\t||\t" << GREEN << "|###### #### |##     |## |## |## |# |## |## |# |## |###### |#####   |##     |###### " << RESET << YELLOW << "                      || \t |\n";
    cout << RESET << YELLOW << "|" << "\t||\t" << GREEN << "|##          |##     |## |## |##    |## |##    |## |##     |## |##  |##     |##       " << RESET << YELLOW << "                    || \t |\n";
    cout << RESET << YELLOW << "|" << "\t||\t" << GREEN << "|######      |###### |###### |##    |## |##    |## |###### |##  |## |###### |######  |EDITION 2.14v5.5 " << RESET<<YELLOW<< "   || \t |\n";
    cout << RESET << YELLOW << "|" << "\t||\t" << "                                                                                                          || \t |\n";
    cout << RESET << YELLOW << "|" << "\t||\t" << "                                                                                                          || \t |\n";
    cout << RESET << YELLOW << "|" << string(128, '=') << "|" << endl;
    cout << RESET << YELLOW << "|" << "\t||\t" << setw(115) << "||      |\n";
    cout << RESET << YELLOW << "|" << "\t||\t" << setw(115) << "||      |\n";

    const char* options[6] = {
      "|LOGIN|",
      "|REGISTER|",
      "|ABOUT|",
      "|SAVE ALL|",
      "|EXIT|"
    };


    for (int i = 0; i < 5; i++) {
        if (cursor == i + 1)
        {
            cout << "|\t||\t\t\t\t\t\t   " << "~< " << options[i] << " >~" << setw(66 - strlen(options[i])) << "||      |\n";
            cout << "|" << "\t||\t" << setw(115) << "||      |\n";
            cout << "|" << "\t||\t" << setw(115) << "||      |\n";
        }
        else
        {
            cout << "|\t||\t\t\t\t\t\t" << i + 1 << ". " << options[i] << setw(72 - strlen(options[i])) << "||      |\n";
            cout << "|" << "\t||\t" << setw(115) << "||      |\n";
            cout << "|" << "\t||\t" << setw(115) << "||      |\n";
        }
    }

    cout << "|" << string(128, '-') << "|" << endl;
    cout << "|" << setw(94) << "Use UP/DOWN arrows or direct numbers for navigation| ENTER to select | ESC to exit" << setw(35) << "|" << endl;
    cout << "|" << string(128, '-') << "|" << endl;
}


int main() {







    int total_users = 0;

    User* user[70];
    for (int i = 0; i < 70; i++) {
        user[i] = nullptr;
    }
    user[0] = new Admin("Abdullah", "abdullahz07");
    User::userCount++;


    string roles[70];
    FileManager::load_all(user, roles, Buyer::userCount, products, product_count); // auto_load
    int count = 0;

    Authentication auth;
    int cursor = 1;
    int input;

    while (true) {
        Menu(cursor);


        input = _getch();

        if (input == 27)
            return 0;

        if (input == 72)
            cursor = (cursor == 1) ? 6 : cursor - 1;

        else if (input == 80)
            cursor = (cursor == 6) ? 1 : cursor + 1;
        else if (input >= '1' && input <= '6')
            cursor = input - '0';


        else if (input == 13) {
            switch (cursor) {
            case 1:
                system("cls");
                auth.login(user);
                system("pause");
                break;

            case 2: {
                system("cls");
                cout << "Select your role\nEnter s for seller and b for buyer =  ";
                char r;
                cin >> r;

                string name, pass;
                cout << "ENTER THE USERNAME = ";
                cin >> name;
                cout << "ENTER THE PASSWORD = ";
                cin >> pass;

                if (r == 's' || r == 'S') {
                    user[count] = new Seller(name, pass);
                    roles[count] = "seller";
                    count++;
                    User::userCount++;
                    cout << "Seller account created\n";
                }
                else if (r == 'b' || r == 'B') {
                    user[count] = new Buyer(name, pass);
                    roles[count] = "buyer";
                    count++;
                    User::userCount++;
                    cout << "Buyer account created\n";
                }
                else {
                    cout << "Invalid role\n";
                }

                system("pause");
                break;
            }
                  //saving
            case 4:
                FileManager::save_all(user, roles, Buyer::userCount, products, product_count);
                cout << "All saved\n";
                system("pause");
                break;



            case 3:
                system("cls");
                cout << "note1|no_current_notes/Complete file ready for execution|note2| ... |note3|save load imp in case main 8/5/25|note4|SUp chaury\n";
                system("pause");
                break;

            case 5: // EXIT
                return 0;
            }

        }
    }
    FileManager::save_all(user, roles, Buyer::userCount, products, product_count);
    system("pause");

    return 0;
}
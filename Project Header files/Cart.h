#pragma once
#include <iostream>
using namespace std;

#define MaxCartitems 10

template <class T>
class cart {


public:
    T* p[MaxCartitems];
    int current_Product_to_return = 0;
    int Items_Added = 0;

    cart() {
        for (int i = 0; i < MaxCartitems; ++i) p[i] = nullptr;
        current_Product_to_return = 0;
        Items_Added = 0;
    }

    // return product pointer at index (no state change)
    T* getProductAt(int idx) const {
        if (idx < 0 || idx >= Items_Added) return nullptr;
        return p[idx];
    }

    // return next product using internal iterator (advances iterator)
    T* getNextProduct() {
        if (current_Product_to_return >= Items_Added) return nullptr;
        return p[current_Product_to_return++];
    }

    // reset iterator so getNextProduct starts from beginning again
    void resetIterator() {
        current_Product_to_return = 0;
    }

    void operator+=(T* obj) {
        if (Items_Added >= MaxCartitems) {
            cout << "CART IS FULL" << endl;
            return;
        }
        p[Items_Added++] = obj;
    }

    void operator-=(const T& obj) {
        for (int i = 0; i < Items_Added; i++) {
            if (p[i] && p[i]->ProductID == obj.ProductID) {
                for (int j = i; j < Items_Added - 1; j++) p[j] = p[j + 1];
                p[Items_Added - 1] = nullptr;
                Items_Added--;
                if (current_Product_to_return > Items_Added) current_Product_to_return = Items_Added;
                break;
            }
        }
    }

    void clear() {
        for (int i = 0; i < Items_Added; ++i) p[i] = nullptr;
        Items_Added = 0;
        current_Product_to_return = 0;
    }

    friend ostream& operator<<(ostream& out, const cart<T>& obj) {
        for (int i = 0; i < obj.Items_Added; i++) {
            if (obj.p[i]) obj.p[i]->displayDetails();
        }
        return out;
    }
};
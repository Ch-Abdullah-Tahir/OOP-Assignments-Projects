#pragma once

#include <iostream>
#include <string>

using namespace std;



class ECommerceException {
protected:
    string message;
public:
    ECommerceException(const string& msg) : message(msg) {}
    virtual const string& what() const { return message; }
    virtual ~ECommerceException() {}
};


class InvalidLoginException : public ECommerceException {
public:
    InvalidLoginException(const string& msg = "Invalid login credentials")
        : ECommerceException(msg) {
    }
};


class OutOfStockException : public ECommerceException {
public:
    OutOfStockException(const string& productName = "Product")
        : ECommerceException(productName + " is out of stock!") {
    }
};


class CartOperationException : public ECommerceException {
public:
    CartOperationException(const string& msg = "Cart operation failed")
        : ECommerceException(msg) {
    }
};

// Product ni milta tou :
class ProductNotFoundException : public ECommerceException {
public:
    ProductNotFoundException(int productId)
        : ECommerceException("Product with ID " + to_string(productId) + " not found") {
    }
};


class FileOperationException : public ECommerceException {
public:
    FileOperationException(const string& filename)
        : ECommerceException("File operation failed for =  " + filename) {
    }
};

class InvalidUserRoleException : public ECommerceException {
public:
    InvalidUserRoleException(const string& role)
        : ECommerceException("Invalid user role =  " + role) {
    }
};
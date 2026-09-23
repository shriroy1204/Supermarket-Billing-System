# Supermarket Billing System

A console-based Supermarket Billing System built in C++ using inheritance, polymorphism, and file handling.

## Features

- Pre-loaded supermarket inventory
- Three product categories:
  - Grocery
  - Electronics
  - Household
- Common base class with derived product classes
- Inheritance and virtual functions (polymorphism)
- Category-based product selection
- Bill generation with customer and bill details
- Automatic stock reduction after billing
- Persistent product stock using `products.txt`
- Billing history stored in `billing.txt`
- Billing history can be retrieved across program runs

## Concepts Used

- Classes and Objects
- Inheritance
- Polymorphism
- Virtual Functions
- Arrays
- Functions
- Dynamic Memory Allocation
- File Handling using `fstream`

## Files

```text
SupermarketBilling.cpp
README.md
.gitignore
```

The program creates these runtime files when used:

```text
products.txt
billing.txt
```

## How to Run

Compile the program using a C++ compiler:

```bash
g++ SupermarketBilling.cpp -o SupermarketBilling
```

Run it:

```bash
./SupermarketBilling
```

On Windows:

```bash
SupermarketBilling.exe
```

## Main Menu

```text
1. Show Inventory
2. Generate Bill
3. Billing History
4. Exit
```

## Author

Developed as a C++ project demonstrating Object-Oriented Programming and file handling.

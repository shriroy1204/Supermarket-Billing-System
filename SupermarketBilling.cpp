#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_PRODUCTS = 100;

class Product {
protected:
    string id;
    string name;
    double price;
    int quantity;

public:
    Product() {
        price = 0.0;
        quantity = 0;
    }

    void setCommon(string i, string n, double p, int q) {
        id = i;
        name = n;
        price = p;
        quantity = q;
    }

    virtual void displayData() {
        cout << id << "\t" << name << "\t" << price << "\t" << quantity;
    }

    virtual string getType() {
        return "Product";
    }

    virtual void saveToFile(ofstream &fout) {
        fout << getType() << "|" << id << "|" << name << "|" << price << "|" << quantity << "\n";
    }

    string getID() { return id; }
    string getName() { return name; }
    double getPrice() { return price; }
    int getQuantity() { return quantity; }
    void reduceQuantity(int q) { quantity -= q; }

    virtual ~Product() {}
};

class Grocery : public Product {
private:
    string expiryDate;

public:
    void displayData() override {
        Product::displayData();
        cout << "\t" << expiryDate << "\tGrocery" << endl;
    }

    string getType() override { return "Grocery"; }

    void saveToFile(ofstream &fout) override {
        fout << getType() << "|" << id << "|" << name << "|" << price << "|"
             << quantity << "|" << expiryDate << "\n";
    }

    void setExpiryDate(string e) { expiryDate = e; }
};

class Electronics : public Product {
private:
    int warrantyMonths;

public:
    Electronics() { warrantyMonths = 0; }

    void displayData() override {
        Product::displayData();
        cout << "\t" << warrantyMonths << "m\tElectronics" << endl;
    }

    string getType() override { return "Electronics"; }

    void saveToFile(ofstream &fout) override {
        fout << getType() << "|" << id << "|" << name << "|" << price << "|"
             << quantity << "|" << warrantyMonths << "\n";
    }

    void setWarranty(int w) { warrantyMonths = w; }
};

class HouseholdProduct : public Product {
private:
    string brand;

public:
    void displayData() override {
        Product::displayData();
        cout << "\t" << brand << "\tHousehold" << endl;
    }

    string getType() override { return "Household"; }

    void saveToFile(ofstream &fout) override {
        fout << getType() << "|" << id << "|" << name << "|" << price << "|"
             << quantity << "|" << brand << "\n";
    }

    void setBrand(string b) { brand = b; }
};

Product* inventory[MAX_PRODUCTS];
int productCount = 0;

void initializeInventory() {
    
    Grocery* g1 = new Grocery();
    g1->setCommon("G101", "Basmati Rice 5kg", 450, 20);
    g1->setExpiryDate("15-03-2027");
    inventory[productCount++] = g1;

    Grocery* g2 = new Grocery();
    g2->setCommon("G102", "Sugar 1kg", 45, 50);
    g2->setExpiryDate("10-01-2028");
    inventory[productCount++] = g2;

    Grocery* g3 = new Grocery();
    g3->setCommon("G103", "Cooking Oil 1L", 150, 30);
    g3->setExpiryDate("20-06-2027");
    inventory[productCount++] = g3;

    Electronics* e1 = new Electronics();
    e1->setCommon("E201", "LED Bulb 9W", 120, 50);
    e1->setWarranty(12);
    inventory[productCount++] = e1;

    Electronics* e2 = new Electronics();
    e2->setCommon("E202", "Mixer Grinder", 2500, 10);
    e2->setWarranty(24);
    inventory[productCount++] = e2;

    Electronics* e3 = new Electronics();
    e3->setCommon("E203", "Extension Cord", 350, 15);
    e3->setWarranty(6);
    inventory[productCount++] = e3;

    HouseholdProduct* h1 = new HouseholdProduct();
    h1->setCommon("H301", "Detergent Powder 1kg", 110, 40);
    h1->setBrand("Surf Excel");
    inventory[productCount++] = h1;

    HouseholdProduct* h2 = new HouseholdProduct();
    h2->setCommon("H302", "Plastic Bucket", 180, 25);
    h2->setBrand("Cello");
    inventory[productCount++] = h2;

    HouseholdProduct* h3 = new HouseholdProduct();
    h3->setCommon("H303", "Broom", 90, 35);
    h3->setBrand("Gala");
    inventory[productCount++] = h3;
}

void showInventory() {
    cout << "\n---- Current Inventory ----\n";
    cout << "ID\tName\t\tPrice\tQty\tExtra\t\tCategory\n";
    for (int i = 0; i < productCount; i++) {
        inventory[i]->displayData();
    }
}

void showCategory(string type) {
    cout << "\nID\tName\t\tPrice\tQty\tExtra\t\tCategory\n";
    for (int i = 0; i < productCount; i++) {
        if (inventory[i]->getType() == type) {
            inventory[i]->displayData();
        }
    }
}

void saveProductsToFile() {
    ofstream fout("products.txt");
    for (int i = 0; i < productCount; i++) {
        inventory[i]->saveToFile(fout);
    }
    fout.close();
}

void generateBill() {
    string billID, custName;
    cout << "\nEnter Bill ID: ";
    cin >> billID;
    cout << "Enter Customer Name: ";
    cin.ignore();
    getline(cin, custName);

    string itemIDs[50];
    int itemQty[50];
    int itemCount = 0;
    double totalAmount = 0.0;

    char more = 'y';
    while (more == 'y' || more == 'Y') {
        int catChoice;
        cout << "\nSelect Category:\n1. Grocery\n2. Electronics\n3. Household\n4. Exit\nChoice: ";
        cin >> catChoice;

        if (catChoice == 4) {
            cout << "Exiting billing selection...\n";
            break;
        }

        string type;
        if (catChoice == 1) type = "Grocery";
        else if (catChoice == 2) type = "Electronics";
        else if (catChoice == 3) type = "Household";
        else {
            cout << "Invalid category!\n";
            continue;
        }

        showCategory(type);

        string pid;
        cout << "Enter Product ID to buy: ";
        cin >> pid;

        int index = -1;
        for (int i = 0; i < productCount; i++) {
            if (inventory[i]->getID() == pid && inventory[i]->getType() == type) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Product not found in this category!\n";
        } else {
            int qty;
            cout << "Enter Quantity: ";
            cin >> qty;

            if (qty > inventory[index]->getQuantity()) {
                cout << "Not enough stock! Available: " << inventory[index]->getQuantity() << endl;
            } else {
                itemIDs[itemCount] = pid;
                itemQty[itemCount] = qty;
                itemCount++;
                totalAmount += inventory[index]->getPrice() * qty;
                inventory[index]->reduceQuantity(qty);
            }
        }

        cout << "Add more items? (y/n): ";
        cin >> more;
    }

    if (itemCount == 0) {
        cout << "No items billed.\n";
        return;
    }

    ofstream fout("billing.txt", ios::app);

    cout << "\n---------- BILL ----------\n";
    cout << "Bill ID: " << billID << "\nCustomer: " << custName << "\n";
    fout << "Bill ID: " << billID << "\nCustomer: " << custName << "\n";

    for (int i = 0; i < itemCount; i++) {
        int index = -1;
        for (int j = 0; j < productCount; j++) {
            if (inventory[j]->getID() == itemIDs[i]) { index = j; break; }
        }
        if (index != -1) {
            double subtotal = inventory[index]->getPrice() * itemQty[i];
            cout << inventory[index]->getName() << "\tQty: " << itemQty[i]
                 << "\tPrice: " << inventory[index]->getPrice()
                 << "\tSubtotal: " << subtotal << endl;
            fout << inventory[index]->getName() << "\tQty: " << itemQty[i]
                 << "\tPrice: " << inventory[index]->getPrice()
                 << "\tSubtotal: " << subtotal << "\n";
        }
    }

    cout << "Total Amount: " << totalAmount << "\n---------------------------\n";
    fout << "Total Amount: " << totalAmount << "\n---------------------------\n";
    fout.close();

    cout << "Bill saved to billing.txt\n";

    saveProductsToFile(); 
}

void showBillingHistory() {
    ifstream fin("billing.txt");
    if (!fin) {
        cout << "\nNo billing history found yet.\n";
        return;
    }

    cout << "\n---- Billing History ----\n";
    string line;
    bool anyLine = false;
    while (getline(fin, line)) {
        cout << line << "\n";
        anyLine = true;
    }
    if (!anyLine) cout << "No billing history found yet.\n";
    fin.close();
}

int main() {
    initializeInventory();

    int choice;
    do {
        cout << "\n===== SUPERMARKET BILLING SYSTEM =====\n";
        cout << "1. Show Inventory\n";
        cout << "2. Generate Bill\n";
        cout << "3. Billing History\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: showInventory(); break;
            case 2: generateBill(); break;
            case 3: showBillingHistory(); break;
            case 4: cout << "Exiting... Thank you!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    for (int i = 0; i < productCount; i++) delete inventory[i];
    return 0;
}

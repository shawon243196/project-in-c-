#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


class Item {
protected:
    int id;
    string name;
    double price;

public:
    virtual void input() {
        cout << "Enter iD: ";
        cin >> id;
        cin.ignore();
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter price: ";
        cin >> price;
    }

    virtual void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Price: " << price;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }

    void setId(int i) { id = i; }
    void setName(const string& n) { name = n; }
    void setPrice(double p) { price = p; }
};


class Product : public Item {
private:
    int quantity;
    string deadline;
    string category;

public:
    void input() override
    {
        Item::input();
        cout << "Enter Quantity: ";
        cin >> quantity;
        cin.ignore();
        cout << "Enter Deadline (e.g. 2025-12-31): ";
        getline(cin, deadline);
        cout << "Enter Category: ";
        getline(cin, category);
    }

    void display() const override
    {
        Item::display();
        cout << " Quantity : " << quantity<<endl;
            cout<< " Deadline : " << deadline<<endl;
            cout<< " Category : " << category << endl;
    }

    void saveToFile(ofstream& file) const
     {
        file << getId() << endl;
        file << getName() << endl;
        file << getPrice() << endl;
        file << quantity << endl;
        file << deadline << endl;
        file << category << endl;
    }

    void loadFromFile(ifstream& file) {
        string line;
        getline(file, line); setId(stoi(line));
        getline(file, line); setName(line);
        getline(file, line); setPrice(stod(line));
        getline(file, line); quantity = stoi(line);
        getline(file, deadline);
        getline(file, category);
    }

    int getQuantity() const { return quantity; }
    string getCategory() const { return category; }
    string getDeadline() const { return deadline; }

    void setQuantity(int q)
    {
        quantity = q;

    }

    void update() {
        cout << "Current Quantity: " << quantity << " Price: " << getPrice() << endl;
        cout << "Enter new Quantity: ";
        cin >> quantity;
        cout << "Enter new Price: ";
        double newPrice;
        cin >> newPrice;
        setPrice(newPrice);
        cin.ignore();
        cout << "Enter new Deadline: ";
        getline(cin, deadline);
        cout << "Enter new Category: ";
        getline(cin, category);
    }
};


class Shop {
private:
    vector<Product> products;

public:
    void addProduct() {
        Product p;
        p.input();
        products.push_back(p);
        cout << " Product added "<<endl;
    }

    void viewProducts() const {
        cout << " Product List :"<<endl;
        for (const auto& p : products) {
            p.display();
        }
    }

    void viewByCategory() const {
        string cat;
        cout << "Enter category to view: ";
        cin.ignore();
        getline(cin, cat);
        bool found = false;
        for (const auto& p : products) {
            if (p.getCategory() == cat) {
                p.display();
                found = true;
            }
        }
        if (!found) cout << " No products found in the categor"<<endl;
    }

    void searchProduct() const {
        string name;
        cout << "Enter product name to search: ";
        cin.ignore();
        getline(cin, name);
        for (const auto& p : products) {
            if (p.getName() == name) {
                cout << " Found: "<<endl;
                p.display();
                return;
            }
        }
        cout << " Product not found"<<endl;
    }

    void deleteProduct() {
        int id;
        cout << "Enter Product ID to delete: ";
        cin >> id;
        for (auto it = products.begin(); it != products.end(); ++it) {
            if (it->getId() == id) {
                products.erase(it);
                cout << " Product deleted "<<endl;
                return;
            }
        }
        cout << " Product not found "<<endl;
    }

    void updateProduct() {
        int id;
        cout << "Enter Product ID : ";
        cin >> id;
        for (auto& p : products) {
            if (p.getId() == id) {
                p.update();
                cout << " Product updated "<<endl;
                return;
            }
        }
        cout << " Product not found "<<endl;
    }


void makeSale() {
    int id, qty;
    cout << "Enter Product ID to sell: ";
    cin >> id;
    for (auto& p : products) {
        if (p.getId() == id) {
            cout << "Available Quantity: " << p.getQuantity() << endl;
            cout << "Enter Quantity to sell: ";
            cin >> qty;
            if (qty > p.getQuantity()) {
                cout << "Not enough stock available" << endl;
                return;
            }
            double total = qty * p.getPrice();
            cout << "Total Bill: " << total << " Taka" << endl;


            int updatedQty = p.getQuantity() - qty;
            p.setQuantity(updatedQty);
            cout << "Remaining Quantity: " << updatedQty << endl;
            return;
        }
    }
    cout << "Product not found" << endl;
}





    void saveToFile() const {
        ofstream file("project.txt");
        file << products.size() << endl;
        for (const auto& p : products) {
            p.saveToFile(file);
        }
        file.close();
        cout << " Products save to file "<<endl;
    }

    void loadFromFile() {
        ifstream file("project.txt");
        if (!file) {
            cout << "  not found "<<endl;
            return;
        }
        int count;
        file >> count;
        file.ignore();
        products.clear();
        for (int i = 0; i < count; ++i) {
            Product p;
            p.loadFromFile(file);
            products.push_back(p);
        }
        file.close();
        cout << " loaded from file "<<endl;
    }
};


int main() {
    Shop shop;
    int choice;

    do {
        cout << "\n**  Shop Management Menu  **"<<endl;
        cout << "1. Add Product"<<endl;
        cout << "2. View All Product"<<endl;
        cout << "3. View Products by Category"<<endl;
        cout << "4. Search Product"<<endl;
        cout << "5. Delete Product  "<<endl;
        cout << "6. Update Product "<<endl;
        cout << "7. Save to File"<<endl;
        cout << "8. Load from File"<<endl;
        cout << "9. Sale product " << endl;
        cout << "0. ..Exit.."<<endl;
        cout << " Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: shop.addProduct();
                break;
            case 2: shop.viewProducts();
              break;
            case 3: shop.viewByCategory();
                 break;
            case 4: shop.searchProduct();
               break;
            case 5: shop.deleteProduct();
               break;
            case 6: shop.updateProduct();
               break;
            case 7: shop.saveToFile();
                break;
            case 8: shop.loadFromFile();
               break;
               case 9: shop.makeSale();
               break;
             case 0: cout << " Exit "<<endl;
               break;
            default: cout << "  choice not found "<<endl;
        }
    } while (choice != 0);

    return 0;
}

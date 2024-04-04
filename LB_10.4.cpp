#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct Car {
    string brand;
    double price;
};

struct Company {
    string name;
    vector<Car> cars;
};

void inputCompany(Company& company) {
    cout << "Enter company name: ";
    cin >> company.name;

    int numCars;
    cout << "Enter number of car models: ";
    cin >> numCars;

    company.cars.resize(numCars);
    for (int i = 0; i < numCars; ++i) {
        cout << "Enter car brand and price: ";
        cin >> company.cars[i].brand >> company.cars[i].price;
    }
}

void printCompany(const Company& company) {
    cout << "Company: " << company.name << "\n";
    for (const auto& car : company.cars) {
        cout << "Car brand: " << car.brand << ", Price: " << car.price << "\n";
    }
}

void saveToFile(const vector<Company>& companies, const string& filename) {
    ofstream file(filename);
    for (const auto& company : companies) {
        file << company.name << " ";
        for (const auto& car : company.cars) {
            file << car.brand << " " << car.price << " ";
        }
        auto maxPriceIt = max_element(company.cars.begin(), company.cars.end(), [](const Car& a, const Car& b) { return a.price < b.price; });
        file << maxPriceIt->price << "\n";
    }
    file.close();
}

void loadFromFile(vector<Company>& companies, const string& filename) {
    ifstream file(filename);
    Company company;
    Car car;
    while (file >> company.name) {
        while (file >> car.brand >> car.price) {
            company.cars.push_back(car);
        }
        companies.push_back(company);
        company.cars.clear();
    }
    file.close();
}

int main() {
    vector<Company> companies;
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    cin.ignore(); 

    loadFromFile(companies, filename);

    while (true) {
        cout << "1. Add company\n2. Print company\n3. Print all companies\n4. Save and exit\n";
        int choice;
        cin >> choice;
        if (choice == 1) {
            Company company;
            inputCompany(company);
            companies.push_back(company);
        }
        else if (choice == 2) {
            string name;
            cout << "Enter company name: ";
            cin >> name;
            auto it = find_if(companies.begin(), companies.end(), [name](const Company& company) { return company.name == name; });
            if (it != companies.end()) {
                printCompany(*it);
            }
        }
        else if (choice == 3) {
            for (const auto& company : companies) {
                printCompany(company);
                cout << endl;
            }
        }
        else if (choice == 4) {
            saveToFile(companies, filename);
            break;
        }
    }

    return 0;
}

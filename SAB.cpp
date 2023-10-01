#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Contact {
public:
    string name;
    string email;
    string phone;

    Contact(const string& n, const string& e, const string& p) : name(n), email(e), phone(p) {}
};

class AddressBook {
private:
    vector<Contact> contacts;
    string filename;

public:
    AddressBook(const string& file) : filename(file) {
        LoadFromFile();
    }

    void AddContact(const string& name, const string& email, const string& phone) {
        Contact newContact(name, email, phone);
        contacts.push_back(newContact);
        SaveToFile();
    }

    void ViewContacts() {
        if (contacts.empty()) {
            cout << "Address book is empty." << endl;
            return;
        }

        cout << "Contacts:" << endl;
        for (const Contact& contact : contacts) {
            cout << "Name: " << contact.name << ", Email: " << contact.email << ", Phone: " << contact.phone << endl;
        }
    }

private:
    void LoadFromFile() {
        contacts.clear();
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            string name, email, phone;
            while (getline(inputFile, name) && getline(inputFile, email) && getline(inputFile, phone)) {
                contacts.emplace_back(name, email, phone);
            }
            inputFile.close();
        }
    }

    void SaveToFile() {
        ofstream outputFile(filename);
        if (outputFile.is_open()) {
            for (const Contact& contact : contacts) {
                outputFile << contact.name << endl << contact.email << endl << contact.phone << endl;
            }
            outputFile.close();
        }
    }
};

int main() {
    const string dataFile = "contacts.txt";
    AddressBook addressBook(dataFile);

    while (true) {
        cout << "Address Book" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. View Contacts" << endl;
        cout << "3. Quit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, email, phone;

            cout << "Enter contact name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter contact email: ";
            getline(cin, email);
            cout << "Enter contact phone: ";
            getline(cin, phone);

            addressBook.AddContact(name, email, phone);
            break;
        }
        case 2:
            addressBook.ViewContacts();
            break;
        case 3:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}

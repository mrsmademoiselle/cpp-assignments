#include <iostream>
#include <fstream>
#include <list>
#include <random>
#include <algorithm>

// Improve code readability for console output
#define PRINT(x) (cout << (x) << endl);
using namespace std;

// Classes and operator overloads
class Motorcycle {
private:
    string name, id;

public:
    ~Motorcycle() {}

    Motorcycle() {}

    Motorcycle(string mName, string mId) {
        name = mName;
        id = mId;
    }

    bool operator<(const Motorcycle &m) const {
        return name < m.name;
    }

    bool operator==(Motorcycle m) const {
        return name == m.name;
    }

    friend ostream &operator<<(ostream &os, const Motorcycle &m);
    friend istream &operator>>(istream &is, Motorcycle &m);

    // Constructor for creating a temporary Motorcycle object during user input in the reservation process.
    Motorcycle(string mName) {
        name = mName;
    }

    void setName(string basicString) {
        name = basicString;
    }

    string getName() const {
        return name;
    }

    string getId() const {
        return id;
    }
};

istream &operator>>(istream &is, Motorcycle &m) {
    is >> m.id;
    is >> m.name;

    return is;
}

ostream &operator<<(ostream &os, const Motorcycle &m) {
    os << m.id << " " << m.name;
    return os;
}

class Customer {
private:
    string firstName, lastName, street, houseNumber, city, phoneNumber, birthYear, postalCode, id;
    bool hasClassA;

    void fill() {
        cout << "Please enter customer data." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "First Name: " << endl;
        getline(cin, firstName);
        cout << "Last Name:" << endl;
        getline(cin, lastName);
        cout << "Street:" << endl;
        getline(cin, street);
        cout << "House Number:" << endl;
        cin >> houseNumber;
        cout << "Postal Code:" << endl;
        cin >> postalCode;
        cout << "City:" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, city);
        cout << "Birth Year:" << endl;
        cin >> birthYear;
        cout << "Phone Number:" << endl;
        cin >> phoneNumber;

        bool fieldSet = false;
        string classA;

        while (!fieldSet) {
            cout << "Driving License Class A:" << endl;
            cout << "0 no" << endl;
            cout << "1 yes" << endl;
            cin >> classA;

            if (classA == "0" || classA == "1") {
                fieldSet = true;
            }
        }
        hasClassA = classA == "1";
    }

public:
    ~Customer() {}

    // Constructor for new customers, string fields do not need to be initialized
    Customer(string cid) : hasClassA(false) {
        id = cid;
        fill();
    }

    // Constructor for testing purposes
    Customer(int i, string cid) : lastName(to_string(i)), firstName(to_string(i)), street("Sample Street"),
                                   houseNumber(to_string(i)), postalCode("11111" + to_string(i)), city("Sample City"),
                                   birthYear("197" + to_string(i)), phoneNumber("1234456879" + to_string(i)),
                                   hasClassA(true), id(cid) {
    }

    Customer() {}

    // Creates a temporary customer object during the reservation/cancellation process.
    Customer(string cFirstName, string cLastName) : hasClassA(false) {
        firstName = cFirstName;
        lastName = cLastName;
    }

    bool operator<(const Customer &c) const {
        return firstName < c.firstName && lastName < c.lastName;
    }

    bool operator==(const Customer &c) const {
        return firstName == c.firstName && lastName == c.lastName;
    }

    friend ostream &operator<<(ostream &os, const Customer &customer);
    friend istream &operator>>(istream &is, Customer &customer);

    void print() const {
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Address: " << street << " " << houseNumber << " " << postalCode << " " << city << endl;
        cout << "Phone Number: " << phoneNumber << " " << endl;
        string hasLicense = hasClassA ? "Has" : "Doesn't have";
        cout << hasLicense << " Driving License Class A" << endl;
        PRINT("-----------------")
    }

    bool hasLicenseA() const {
        return hasClassA;
    }

    string getFirstName() const {
        return firstName;
    }

    string getLastName() const {
        return lastName;
    }

    string getId() const {
        return id;
    }

    void setFirstName(string basicString) {
        firstName = basicString;
    }

    void setLastName(string basicString) {
        lastName = basicString;
    }
};

istream &operator>>(istream &is, Customer &customer) {
    is >> customer.id;
    is >> customer.firstName;
    is >> customer.lastName;
    is >> customer.birthYear;
    is >> customer.hasClassA;
    is >> customer.phoneNumber;
    is >> customer.street;
    is >> customer.houseNumber;
    is >> customer.postalCode;
    is >> customer.city;

    return is;
}

ostream &operator<<(ostream &os, const Customer &customer) {
    os << customer.id << " " << customer.firstName << " " << customer.lastName << " " << customer.birthYear << " "
       << customer.hasClassA << " " << customer.phoneNumber << " " << customer.street << " " << customer.houseNumber
       << " " << customer.postalCode << " " << customer.city;
    return os;
}

class Reservation {
private:
    Motorcycle motorcycle;
    Customer customer;
    string startDate, endDate;

public:
    Reservation() {}

    Reservation(Motorcycle m, Customer c, string sDate, string eDate) : motorcycle(m), customer(c),
                                                                         startDate(sDate), endDate(eDate) {}

    bool operator==(const Reservation &r) const {
        return motorcycle == r.motorcycle && customer == r.customer && startDate == r.startDate && endDate == r.endDate;
    }

    friend ostream &operator<<(ostream &os, const Reservation &reservation);
    friend istream &operator>>(istream &is, Reservation &reservation);

    void print() const {
        motorcycle.print();
        customer.print();
        PRINT("Reservation Period: " + startDate + " to " + endDate)
    }
};

istream &operator>>(istream &is, Reservation &reservation) {
    is >> reservation.motorcycle;
    is >> reservation.customer;
    is >> reservation.startDate;
    is >> reservation.endDate;

    return is;
}

ostream &operator<<(ostream &os, const Reservation &reservation) {
    os << reservation.motorcycle << " " << reservation.customer << " " << reservation.startDate << " "
       << reservation.endDate;
    return os;
}

// Helper functions
template<typename T>
void printList(const list<T> &lst) {
    for (const auto &elem : lst) {
        elem.print();
        PRINT("-----------------")
    }
}

template<typename T>
void saveList(const list<T> &lst, const string &filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (const auto &elem : lst) {
            file << elem << endl;
        }
        file.close();
        PRINT("Data saved to file: " + filename)
    } else {
        cerr << "Unable to open file: " + filename << endl;
    }
}

template<typename T>
void loadList(list<T> &lst, const string &filename) {
    ifstream file(filename);

    if (file.is_open()) {
        T temp;
        while (file >> temp) {
            lst.push_back(temp);
        }
        file.close();
        PRINT("Data loaded from file: " + filename)
    } else {
        cerr << "Unable to open file: " + filename << endl;
    }
}

int main() {
    list<Motorcycle> motorcycles;
    list<Customer> customers;
    list<Reservation> reservations;

    Motorcycle m1("Honda", "001");
    Motorcycle m2("Yamaha", "002");
    Motorcycle m3("Suzuki", "003");

    motorcycles.push_back(m1);
    motorcycles.push_back(m2);
    motorcycles.push_back(m3);

    Customer c1("John", "Doe");
    Customer c2("Jane", "Smith");
    Customer c3("Bob", "Johnson");

    customers.push_back(c1);
    customers.push_back(c2);
    customers.push_back(c3);

    Reservation r1(m1, c1, "2023-01-01", "2023-01-05");
    Reservation r2(m2, c2, "2023-02-10", "2023-02-15");
    Reservation r3(m3, c3, "2023-03-20", "2023-03-25");

    reservations.push_back(r1);
    reservations.push_back(r2);
    reservations.push_back(r3);

    // Print initial data
    PRINT("Initial Motorcycles:")
    printList(motorcycles);
    PRINT("Initial Customers:")
    printList(customers);
    PRINT("Initial Reservations:")
    printList(reservations);

    // Save data to files
    saveList(motorcycles, "motorcycles.txt");
    saveList(customers, "customers.txt");
    saveList(reservations, "reservations.txt");

    // Clear data
    motorcycles.clear();
    customers.clear();
    reservations.clear();

    // Load data from files
    loadList(motorcycles, "motorcycles.txt");
    loadList(customers, "customers.txt");
    loadList(reservations, "reservations.txt");

    // Print loaded data
    PRINT("Motorcycles after loading:")
    printList(motorcycles);
    PRINT("Customers after loading:")
    printList(customers);
    PRINT("Reservations after loading:")
    printList(reservations);

    return 0;
}

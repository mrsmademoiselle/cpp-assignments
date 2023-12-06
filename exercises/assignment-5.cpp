#include <iostream>
using namespace std;

//5     Linked List (20 minutes)
//
//5.1   Add the necessary attributes to the Employee class for a linked list (compatible with the EmployeeList class).
//
//5.2   Add to the Employee class:
//      a)	Default constructor
//      b)	Parameterized constructor with element initialization list
//      c)	"print" method to output all employee data.
//
//5.3   In the main function, 3 employee objects should be added to the list. Output the data of the employees from the list using a for loop.
//      Expand the program with the required methods for this.

class Employee {
    friend class EmployeeList;

private:
    string name;
    short birthYear;
    Employee* successor;

public:
    Employee() {
        cout << "This is a default constructor." << endl;
    }
    Employee(string n, short j) : name(n), birthYear(j) {
        successor = nullptr;
        cout << "This is an element initialization constructor." << endl;
    }

    void print() {
        cout << "Name: " << name << endl;
        cout << "Birth Year: " << birthYear << endl;
    }

    Employee* next() { return successor; }
};

class EmployeeList {

private:
    Employee* Head;

public:
    EmployeeList() : Head(nullptr) {};

    void insert(Employee* t) {
        string name;
        cout << "Enter name: ";
        cin >> name;

        short birthYear;
        cout << "Enter birth year: ";
        cin >> birthYear;

        t->name = name;
        t->birthYear = birthYear;

        t->successor = Head;
        Head = t;
    }

    Employee* begin() { return Head; }
};

EmployeeList employeeList;
Employee createEmployee();
void outputEmployees();

int main() {
    for (int i = 0; i < 3; i++) {
        // Create Employee
        Employee employee = createEmployee();
    }

    outputEmployees();

    return 0;
}

void outputEmployees() {
    Employee* e;
    for (e = employeeList.begin(); e != nullptr; e = e->next()) {
        e->print();
    }
}

Employee createEmployee() {
    Employee* object = new Employee();
    employeeList.insert(object);

    return *object;
}

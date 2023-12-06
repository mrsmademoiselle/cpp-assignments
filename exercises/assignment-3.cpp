#include <iostream>
using namespace std;

//3     Abstract Classes and Polymorphism (20 minutes)
//
//3.1   Add the appropriate attributes to the "Property" class in the program to match the constructor.
//      These attributes should only be modifiable by derived classes. The program should run error-free afterwards.
//
//3.2   Modify the class in the program to become an abstract base class (using the print() method).
//
//3.3   What is special about abstract base classes?
//      Answer:
//      The inheriting classes are forced to implement the abstract methods, and no instance of the abstract class can be created.
//
//3.4   Add a derived class "Skyscraper" to the program, derived from the abstract class "Property."
//      This class should include the attributes "floors" of type int and "furnished" of type bool, a default constructor,
//      and a constructor with an initializer list.
//      Which method(s) still need(s) to be implemented for the program to run? Implement these method(s).
//      -> The abstract method of the superclass.

class Property {
private:
    float area;
    string location, street;
    static int count;

public:
    Property() { count++; };
    Property(float a, string loc, string st) : area(a), location(loc), street(st) { count++; };
    virtual void print() = 0; // Output of data

};

class Skyscraper : public Property {
private:
    int floors;
    bool furnished;

public:
    Skyscraper() {
        cout << "This is a default constructor." << endl;
    }

    Skyscraper(int f, bool furn) : floors(f), furnished(furn) {
        cout << "This is a constructor with initializer list." << endl;
    }

    void print() override {
        cout << "Floors: " << floors << endl;
        cout << "Furnished: " << furnished << endl;
    }

};

int Property::count = 0;
int main() {

    return 0;
}

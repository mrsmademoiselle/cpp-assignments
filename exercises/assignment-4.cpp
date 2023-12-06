#include <iostream>
using namespace std;

//4     Operator Overloading (25 minutes)

//4.1   Expand the program with an external function that compares 2 objects for equality.
//      If both objects are equal, i.e., the two numbers are equal, output "Equal"; if the objects are not equal, output "Not equal".
//
//4.2   Expand the program with istream >> and ostream << operator overloading. For istream, prompt the user for input for number1 and number2.
//      Using ostream, display the numbers.
//
//4.3   Create two objects of the class Zahlen dynamically. User input for the data should be obtained (via istream from 4.2).
//      Display the entered numbers (via ostream from 4.2). Compare the two objects using the external function from 4.1.

class Zahlen {
private:
    int zahl1, zahl2;

public:
    Zahlen(int z1, int z2) : zahl1(z1), zahl2(z2) {};
    Zahlen() {}

    friend bool operator==(Zahlen&, Zahlen&);
    friend istream& operator>> (istream& is, Zahlen& a);
    friend ostream& operator<< (ostream& os, const Zahlen& b);
};

bool operator== (Zahlen& a, Zahlen& b) {
    return (a.zahl1 == b.zahl1 && a.zahl2 == b.zahl2);
}

istream& operator>> (istream& is, Zahlen& a) {
    cout << endl << "Enter Number 1: ";
    is >> a.zahl1;
    cout << "Enter Number 2: ";
    is >> a.zahl2;
    return is;
}

ostream& operator<< (ostream& os, const Zahlen& a) {
    os << "Number 1: " << a.zahl1 << ", Number 2: " << a.zahl2 << endl;
    return os;
}

int main() {

    Zahlen *number1 = new Zahlen();
    cin >> *number1;
    cout << *number1;

    Zahlen *number2 = new Zahlen();
    cin >> *number2;
    cout << *number2;

    cout << "The objects are " << (*number1 == *number2 ? "equal" : "not equal") << endl;
    return 0;
}

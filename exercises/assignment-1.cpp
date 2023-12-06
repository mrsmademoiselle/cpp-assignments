#include <iostream>
using namespace std;

//1    Basics  (15 minutes)
//
//1.1  Declare a class Candle with the following properties:
//      Height (in cm) and Color. Choose suitable data types. These properties can only be changed by derived classes.
//      Define for the class:
//      a)  Default constructor
//      b)  Parameterized constructor with an initializer list
//      c)  Method 'displayData' to output all data. The 'displayData' method should be defined outside the class.
//
//1.2  Definition of Methods
//      From experience, you know that a candle loses an average of 3 cm in 'Height' per hour.
//      Define a method 'updateHeight' with a parameter 'burningHours' and an appropriate data type.
//      The method's task is to update the 'Height' of the candle based on the hours.
//      If the candle is burnt out after the update, display a corresponding message; otherwise, display the current candle height.
//
//1.3  Dynamic Instantiation
//      Define 2 dynamic instances of the Candle class. The attribute values do not need to be queried
//      and can be statically passed. Call the 'displayData' method for the second instance
//      and call the 'updateHeight' method for the first instance.

class Candle {
private:
    double height;
    string color;

public:
    Candle() {
        cout << "This is a default constructor" << endl;
    }

    Candle(double h, string c) : height(h), color(c) {
        cout << "Constructor with an initializer list" << endl;
        cout << "Height: " << h << endl;
        cout << "Color: " << c << endl;
    }

    friend void displayData(const Candle &c);

    void updateHeight(double burningHours) {
        double currentHeight = height - (burningHours * 3);
        if (currentHeight <= 0.0) {
            height = 0;
            cout << "The candle has burnt out." << endl;
        } else {
            height = currentHeight;
            cout << "The candle is now " << height << "cm tall." << endl;
        }
    }
};

void displayData(const Candle &c) {
    cout << "Height: " << c.height << endl;
    cout << "Color: " << c.color << endl;
}

int main() {
    Candle *candle1 = new Candle(20, "yellow");
    Candle *candle2 = new Candle(10.0, "red");

    candle1->updateHeight(3);
    displayData(*candle2);

    return 0;
}

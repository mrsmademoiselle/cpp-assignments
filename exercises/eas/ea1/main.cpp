#include <iostream>
#include <iterator>
#include <map>
#include <cmath>
#include <algorithm>
#include <set>

#define PRINT(x) (std::cout << (x) << std::endl);

using namespace std;

class IceCream {
public:
    string name;
    double price;

    IceCream(string nameInput, double priceInput) {
        name = nameInput;
        price = priceInput;
    }

    IceCream(string nameInput) {
        transform(nameInput.begin(), nameInput.end(), nameInput.begin(), ::toupper);
        name = nameInput;
    }

    bool operator<(const IceCream &obj) const {
        return name < obj.name;
    }

    void printMe() {
        cout << name << "\t" << price << endl;
    }
};

void takeOrder();
void printIceCreamFlavorsOnConsole();
bool isInStock(const IceCream &iceCreamFlavor);
double calculateTotal();
bool isEnoughMoneyAvailable(const IceCream &);
double roundToTwoDecimals(double);
void addToOrder(const IceCream &);
void finishOrder();
void printOrder();
void askForAnotherOrder();
void suggestCheaperIceCreamFlavor();
void didYouMean(const IceCream &);
double calculateMatchPercentage(const string &, const string &);
string removeDuplicates(const string &);
int countMatchingCharacters(const string &, const string &);
void getIceCreamFlavors();

bool lastOrderReceived = false;
map<IceCream, int> allOrdersWithQuantity;
double availableMoneyInEuro = 5.0;
set<IceCream> allIceCreamFlavors;

int main() {
    getIceCreamFlavors();

    PRINT("Welcome to the Ice Cream Shop!");
    printIceCreamFlavorsOnConsole();

    while (!lastOrderReceived) {
        takeOrder();
    }

    return 0;
}

void getIceCreamFlavors() {
    allIceCreamFlavors.insert(IceCream("CAPRI", 1.10));
    allIceCreamFlavors.insert(IceCream("NOGGER", 1.60));
    allIceCreamFlavors.insert(IceCream("CORNETTO", 2.30));
}

void takeOrder() {
    PRINT("Which ice cream would you like?");
    string desiredIceCreamFlavor;
    cin >> desiredIceCreamFlavor;
    IceCream iceCream = IceCream(desiredIceCreamFlavor);

    if (isInStock(iceCream)) {
        if (isEnoughMoneyAvailable(iceCream)) {
            addToOrder(iceCream);
        } else {
            PRINT("Sorry, the ice cream is too expensive.");
            suggestCheaperIceCreamFlavor();
        }
        if (!lastOrderReceived) askForAnotherOrder();
    } else {
        PRINT("Sorry, we don't have that ice cream flavor in stock.");
        didYouMean(iceCream);
        printIceCreamFlavorsOnConsole();
        takeOrder();
    }
}

void askForAnotherOrder() {
    PRINT("Would you like to order another ice cream? y/n");
    string anotherOrder;
    cin >> anotherOrder;

    transform(anotherOrder.begin(), anotherOrder.end(), anotherOrder.begin(), ::toupper);

    bool willUserEndOrder = anotherOrder == "N" || anotherOrder == "NO";

    if (willUserEndOrder) {
        finishOrder();
    } else {
        bool willUserOrderMore = anotherOrder == "Y" || anotherOrder == "YES";

        if (!willUserOrderMore) {
            PRINT("Sorry, the response could not be parsed.");
            askForAnotherOrder();
        }
    }
}

void addToOrder(const IceCream &orderedIceCreamFlavor) {
    const map<IceCream, int>::iterator &iceCreamPosition = allOrdersWithQuantity.find(orderedIceCreamFlavor);
    bool iceCreamFlavorInOrderExists = iceCreamPosition != allOrdersWithQuantity.end();

    if (iceCreamFlavorInOrderExists) {
        PRINT("There is already at least one ice cream of this flavor in the order. Incrementing...");
        iceCreamPosition->second++;
    } else {
        PRINT("There is no ice cream of this flavor in the order yet. Adding...");
        allOrdersWithQuantity.insert({orderedIceCreamFlavor, 1});
    }
}

void finishOrder() {
    lastOrderReceived = true;
    PRINT("Order is ready. Calculating total...");
    printOrder();
    calculateTotal();
    system("pause");
}

void printOrder() {
    PRINT("\n---------------");
    PRINT("Summary: ");

    for (const auto &orderWithPricePair: allOrdersWithQuantity) {
        cout << orderWithPricePair.second << "x " << orderWithPricePair.first.name << endl;
    }
}

void suggestCheaperIceCreamFlavor() {
    double total = calculateTotal();
    double change = availableMoneyInEuro - total;
    bool isAnotherIceCreamFlavorFeasible = false;

    cout << "The following ice cream flavors would be feasible in terms of price: ";
    for (auto &iceCreamFlavor: allIceCreamFlavors) {
        if (change >= iceCreamFlavor.price) {
            isAnotherIceCreamFlavorFeasible = true;
            PRINT(iceCreamFlavor.name + ". ");
        }
    }

    if (isAnotherIceCreamFlavorFeasible) {
        PRINT("\n");
        printIceCreamFlavorsOnConsole();
    } else {
        PRINT("-\nUnfortunately, you don't have enough money for another ice cream.");
        finishOrder();
    }
}

void didYouMean(const IceCream &userInput) {
    pair<string, int> mostSimilarIceCreamFlavorWithPercentage = {allIceCreamFlavors.begin()->name, 0};

    for (auto &iceCreamFlavor: allIceCreamFlavors) {
        string mainString, testString;

        if (iceCreamFlavor.name.length() >= userInput.name.length()) {
            mainString = iceCreamFlavor.name;
            testString = userInput.name;
        } else {
            mainString = userInput.name;
            testString = iceCreamFlavor.name;
        }
        double matchPercentage = calculateMatchPercentage(mainString, testString);

        if (matchPercentage > mostSimilarIceCreamFlavorWithPercentage.second) {
            mostSimilarIceCreamFlavorWithPercentage = {iceCreamFlavor.name, matchPercentage};
        }
    }
    cout << "Did you mean " << mostSimilarIceCreamFlavorWithPercentage.first << "?" << endl;
}

double calculateMatchPercentage(const string &mainString, const string &testString) {
    const string mainStringWithoutDuplicates = removeDuplicates(mainString);
    const string testStringWithoutDuplicates = removeDuplicates(testString);

    int matchingCharacters = countMatchingCharacters(mainStringWithoutDuplicates, testStringWithoutDuplicates);
    double matchPercentage = 100.00 / (double) testStringWithoutDuplicates.length() * matchingCharacters;

    return matchPercentage;
}

int countMatchingCharacters(const string &mainString, const string &testString) {
    int numberOfMatchingCharacters = 0;

    for (auto &iteratedChar: testString) {
        bool characterExists = mainString.find(iteratedChar) < mainString.length();

        if (characterExists) numberOfMatchingCharacters++;
    }
    return numberOfMatchingCharacters;
}

string removeDuplicates(const string &mainString) {
    string withoutDuplicates;

    for (int i = 0; i < mainString.length(); i++) {
        bool characterDoesNotExist = withoutDuplicates.find(mainString.at(i)) >= mainString.length();

        if (characterDoesNotExist) {
            withoutDuplicates.push_back(mainString.at(i));
        }
    }
    return withoutDuplicates;
}

void printIceCreamFlavorsOnConsole() {
    PRINT("----------------------")
    PRINT("The following ice cream flavors are currently in stock:\n");

    for (auto iceCream: allIceCreamFlavors) {
        iceCream.printMe();
    }

    PRINT("----------------------")
}

bool isInStock(const IceCream &iceCreamFlavor) {
    for (auto &iceCream: allIceCreamFlavors) {
        bool iceCreamFlavorExists = iceCreamFlavor.name == iceCream.name;

        if (iceCreamFlavorExists) {
            PRINT("The flavor " + iceCreamFlavor.name + " is in stock!");
            return true;
        }
    }
    return false;
}

bool isEnoughMoneyAvailable(const IceCream &iceCreamFlavor) {
    double currentTotalAmount = calculateTotal();
    double remainingMoney = availableMoneyInEuro - currentTotalAmount;

    return remainingMoney >= allIceCreamFlavors.find(iceCreamFlavor)->price;
}

double calculateTotal() {
    double totalAmount = 0.0;

    for (auto &orderWithQuantityPair: allOrdersWithQuantity) {
        int orderedQuantityOfThisFlavor = orderWithQuantityPair.second;
        double pricePerUnit = allIceCreamFlavors.find(orderWithQuantityPair.first)->price;
        double pricePerFlavor = (float) orderedQuantityOfThisFlavor * pricePerUnit;

        totalAmount += pricePerFlavor;
    }

    if (lastOrderReceived) {
        cout << "Total: " << roundToTwoDecimals(totalAmount) << "EUR" << endl;
        cout << "Change: " << roundToTwoDecimals(availableMoneyInEuro - totalAmount) << "EUR" << endl;
    }

    return totalAmount;
}

double roundToTwoDecimals(double number) {
    return (roundf(number * 100) / 100);
}

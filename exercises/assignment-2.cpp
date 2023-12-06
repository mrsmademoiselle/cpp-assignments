#include <iostream>
using namespace std;

// Arrays (10 minutes)

// In the program below, a two-dimensional "expenses" array is defined in which the expenses for the last three years are stored over 12 months.
// In the second year, expenses have increased by exactly 20% from the previous year, and in the third year, they have increased by exactly 12% from the previous year for each month.
// Expand the program to precisely accommodate these adjustments to expenses in the second and third years, and store them accordingly in the "expenses" array.
// Finally, display the data using a for loop.

double calculateNewValue(double previousYearValue, double percentage);

int main() {
    double expenses[3][12] = {{10, 15, 20, 36, 15, 45, 20, 35, 24, 64, 52, 12},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    for (int i = 1; i < 3; i++) { // Year, iteration starts from Year 2 because Year 1 is already set
        cout << "----- YEAR: " << i + 1 << " -----" << endl;
        for (int h = 0; h < 12; h++) { // Month

            // Set percentage to increase depending on the year
            double percentage = 0;
            if (i == 1) { // Second year
                percentage = 0.2;
            } else if (i == 2) { // Third year
                percentage = 0.12;
            }

            // Adjust and set value
            double monthInPreviousYear = expenses[i - 1][h];
            double newValue = calculateNewValue(monthInPreviousYear, percentage);
            expenses[i][h] = newValue;

            cout << "-- Month: " << h + 1 << endl;
            cout << "Old Value: " << monthInPreviousYear << ", New Value: " << expenses[i][h] << ", Percentage: " << percentage << endl;
        }
        cout << endl;
    }

    return 0;
}

double calculateNewValue(double previousYearValue, double percentage) {
    return previousYearValue + (previousYearValue * percentage);
}

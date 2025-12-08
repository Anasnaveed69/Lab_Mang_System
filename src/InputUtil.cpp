#include "../include/InputUtil.h"
#include <sstream>

string InputUtil::readString(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

int InputUtil::readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        stringstream ss(input);
        if (ss >> value && ss.eof()) {
            return value;
        }
        cout << "Invalid input. Please enter a valid integer." << endl;
    }
}

// Helper function to validate date
static bool isValidDate(int year, int month, int day) {
    // Check year range (reasonable range)
    if (year < 2000 || year > 2100) {
        return false;
    }
    
    // Check month range
    if (month < 1 || month > 12) {
        return false;
    }
    
    // Days in each month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Check for leap year (simplified: divisible by 4)
    if (month == 2 && (year % 4 == 0)) {
        daysInMonth[1] = 29;
    }
    
    // Check day range
    if (day < 1 || day > daysInMonth[month - 1]) {
        return false;
    }
    
    return true;
}

Date InputUtil::readDate(const string& prompt) {
    Date date;
    while (true) {
        cout << prompt << " (YYYY-MM-DD): ";
        string input;
        getline(cin, input);
        stringstream ss(input);
        char dash1, dash2;
        if (ss >> date.year >> dash1 >> date.month >> dash2 >> date.day && 
            dash1 == '-' && dash2 == '-' && ss.eof()) {
            // Validate the date
            if (isValidDate(date.year, date.month, date.day)) {
                return date;
            } else {
                cout << "Invalid date! Please enter a valid date (e.g., 2024-02-28)." << endl;
            }
        } else {
            cout << "Invalid date format. Please use YYYY-MM-DD." << endl;
        }
    }
}

Time InputUtil::readTime(const string& prompt) {
    Time time;
    while (true) {
        cout << prompt << " (HH:MM): ";
        string input;
        getline(cin, input);
        stringstream ss(input);
        char colon;
        if (ss >> time.hour >> colon >> time.minute && colon == ':' && ss.eof()) {
            return time;
        }
        cout << "Invalid time format. Please use HH:MM." << endl;
    }
}

int InputUtil::readDayOfWeek(const string& prompt) {
    cout << prompt << endl;
    cout << "1. Monday" << endl;
    cout << "2. Tuesday" << endl;
    cout << "3. Wednesday" << endl;
    cout << "4. Thursday" << endl;
    cout << "5. Friday" << endl;
    cout << "6. Saturday" << endl;
    cout << "7. Sunday" << endl;
    while (true) {
        int choice = readInt("Enter choice (1-7): ");
        if (choice >= 1 && choice <= 7) {
            return choice;
        }
        cout << "Invalid choice. Please enter 1-7." << endl;
    }
}

bool InputUtil::readBoolean(const string& prompt) {
    while (true) {
        string input = readString(prompt + " (y/n): ");
        if (input == "y" || input == "Y" || input == "yes" || input == "Yes") {
            return true;
        } else if (input == "n" || input == "N" || input == "no" || input == "No") {
            return false;
        }
        cout << "Invalid input. Please enter 'y' or 'n'." << endl;
    }
}

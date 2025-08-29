#include <bits/stdc++.h>
#include <ctime>
#include <chrono>
#include <iomanip>
using namespace std;

// ----------------------------- MENU DATA -----------------------------
struct Item {
    string name;
    int price;
};

map<int, vector<Item>> menus = {
    {1, {{"Idly", 30}, {"Dosa", 40}, {"Puri", 50}, {"Vada", 20}, {"Pongal", 45}, {"Upma", 35}}},
    {2, {{"Chicken Biryani", 220}, {"Veg Biryani", 170}, {"Rice Meal", 120}, {"Chapathi", 80}, {"Mixed Vegetable Salad", 70}, {"Soup", 60}}},
    {3, {{"Samosa", 40}, {"French Fries", 40}, {"Cutlet", 40}, {"Panipuri", 40}, {"Boiled Groundnuts", 20}, {"Bhel Puri", 40}}},
    {4, {{"Fruit Salad", 65}, {"Jeera Rice", 60}, {"Fried Rice", 40}, {"Curd Rice", 30}, {"Omelette", 40}}}
};

// ---------- TIME HELPERS ----------
struct TimeNow {
    int hhmm;      // e.g., 1200
    string pretty; // "HH:MM"
};

TimeNow getISTTimeAuto() {
    using namespace std::chrono;

    auto now = system_clock::now();
    time_t t = system_clock::to_time_t(now);

    tm loc = *localtime(&t);
    tm gm  = *gmtime(&t);
    int diffMin = (loc.tm_yday - gm.tm_yday) * 24 * 60
                + (loc.tm_hour - gm.tm_hour) * 60
                + (loc.tm_min  - gm.tm_min);

    bool hostIsUTC = std::abs(diffMin) <= 1;
    time_t t_ist = hostIsUTC ? (t + 330 * 60) : t;

    tm ist = hostIsUTC ? *gmtime(&t_ist) : *localtime(&t_ist);
    int hh = ist.tm_hour;
    int mm = ist.tm_min;

    int hhmm = hh * 100 + mm;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hh
        << ":" << std::setw(2) << std::setfill('0') << mm;

    return {hhmm, oss.str()};
}

bool withinGrace(int current, int slot) {
    int lower = slot - 15;
    int upper = slot + 15;
    return current >= lower && current <= upper;
}

void displayMenu(int mealType) {
    cout << "\n--- MENU ---\n";
    const auto &v = menus[mealType];
    for (int i = 0; i < (int)v.size(); i++) {
        cout << i + 1 << ") " << v[i].name << " Rs." << v[i].price << "\n";
    }
}

int readIntInRange(const string &prompt, int lo, int hi) {
    while (true) {
        cout << prompt << flush;
        int x;
        if (cin >> x) {
            if (x >= lo && x <= hi) return x;
            cout << "Please enter a number between " << lo << " and " << hi << ".\n";
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
        }
    }
}

int readPositiveInt(const string &prompt) {
    while (true) {
        cout << prompt << flush;
        int x;
        if (cin >> x) {
            if (x > 0) return x;
            cout << "Quantity must be positive.\n";
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
        }
    }
}

char readYesNo(const string &prompt) {
    while (true) {
        cout << prompt << flush;
        char c;
        if (cin >> c) {
            c = (char)toupper((unsigned char)c);
            if (c == 'Y' || c == 'N') return c;
        }
        cout << "Please enter Y or N.\n";
    }
}

void takeOrder(int mealType, vector<pair<string, pair<int,int>>> &orders, int &total) {
    while (true) {
        displayMenu(mealType);
        int choice = readIntInRange("\nEnter your choice: ", 1, (int)menus[mealType].size());
        int qty    = readPositiveInt("Enter Quantity: ");

        const auto &mi = menus[mealType][choice - 1];
        int itemCost = mi.price * qty;
        orders.emplace_back(mi.name, make_pair(qty, itemCost));
        total += itemCost;

        cout << "Added: " << qty << " x " << mi.name << " = Rs." << itemCost << "\n";
        char more = readYesNo("Do you want to order more? (Y/N): ");
        if (more == 'N') break;
    }
}

void printBill(const vector<pair<string, pair<int,int>>> &orders, int total) {
    cout << "\n========= FINAL BILL =========\n";
    for (const auto &ord : orders) {
        cout << ord.second.first << " x " << ord.first << " - Rs." << ord.second.second << "\n";
    }
    cout << "------------------------------\n";
    cout << "Total: Rs." << total << "\n";
    cout << "Your food will be served in 30 minutes.\n";
    cout << "==============================\n";
}

// ----------------------------- MAIN -----------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string name;
    cout << "Please Enter Your Name: " << flush;
    getline(cin, name);
    while (name.empty()) {
        cout << "Name cannot be empty. Please Enter Your Name: " << flush;
        getline(cin, name);
    }

    // Section time slots per meal (HHMM format)
    map<char, int> breakfastSlot = {
        {'A', 1030}, {'B', 1040}, {'C', 1050}, {'D', 1100},
        {'E', 1110}, {'F', 1120}, {'G', 1130}, {'H', 1140}
    };

    map<char, int> lunchSlot = {
        {'A', 1230}, {'B', 1240}, {'C', 1250}, {'D', 1300},
        {'E', 1310}, {'F', 1320}, {'G', 1330}, {'H', 1340}
    };

    map<char, int> snacksSlot = {
        {'A', 1630}, {'B', 1640}, {'C', 1650}, {'D', 1700},
        {'E', 1710}, {'F', 1720}, {'G', 1730}, {'H', 1740}
    };

    map<char, int> dinnerSlot = {
        {'A', 2030}, {'B', 2040}, {'C', 2050}, {'D', 2100},
        {'E', 2110}, {'F', 2120}, {'G', 2130}, {'H', 2140}
    };

    char section = 0;
    while (true) {
        cout << "Please enter your Section (A-H): " << flush;
        string secLine;
        getline(cin, secLine);
        if (secLine.empty()) continue;

        section = (char)toupper((unsigned char)secLine[0]);
        if (section < 'A' || section > 'H') {
            cout << "Invalid section. Enter a letter A through H.\n";
            continue;
        }

        TimeNow nowIST = getISTTimeAuto();
        int hhmm = nowIST.hhmm;

        cout << "Current Time (IST): " << nowIST.pretty << "  [" << hhmm << "]\n";

        int mealType = 0;

        if (withinGrace(hhmm, breakfastSlot[section])) mealType = 1;
        else if (withinGrace(hhmm, lunchSlot[section])) mealType = 2;
        else if (withinGrace(hhmm, snacksSlot[section])) mealType = 3;
        else if (withinGrace(hhmm, dinnerSlot[section])) mealType = 4;

        if (mealType == 0) {
            cout << "Sorry — It's not your section's meal time.\n";
            cout << "Please come back during your scheduled slot.\n";
            continue;
        }

        cout << "\nHello " << name << " (Section " << section << ")\n";
        cout << "You can order now for: "
             << (mealType == 1 ? "Breakfast" :
                 mealType == 2 ? "Lunch" :
                 mealType == 3 ? "Snacks" : "Dinner")
             << "\n";

        vector<pair<string, pair<int,int>>> orders;
        int total = 0;
        takeOrder(mealType, orders, total);
        printBill(orders, total);

        cout << "\nSelect Payment Method:\n1. UPI\n2. Card\n3. Cash\n";
        int paymentChoice = readIntInRange("Choice: ", 1, 3);
        switch (paymentChoice) {
            case 1: cout << "Processing UPI Payment... Payment Successful!\n"; break;
            case 2: cout << "Processing Card Payment... Payment Successful!\n"; break;
            case 3: cout << "Please pay cash at the counter.\n"; break;
        }

        cout << "\nThank you! Enjoy your meal \n";
        return 0;
    }
}

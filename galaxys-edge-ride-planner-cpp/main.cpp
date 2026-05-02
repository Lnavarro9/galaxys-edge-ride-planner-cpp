#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

struct Ride {
    string name;
    string land;
    int waitTime;
    int priority;
};

// ================= SAVE =================
void saveRides(const vector<Ride>& rides) {
    ofstream file("rides.txt");

    for (const Ride& ride : rides) {
        file << ride.name << "|"
            << ride.land << "|"
            << ride.waitTime << "|"
            << ride.priority << endl;
    }

    file.close();
}

// ================= LOAD =================
void loadRides(vector<Ride>& rides) {
    ifstream file("rides.txt");

    if (!file) return;

    rides.clear();

    string name, land, waitStr, priorityStr;

    while (getline(file, name, '|') &&
        getline(file, land, '|') &&
        getline(file, waitStr, '|') &&
        getline(file, priorityStr)) {

        Ride r;
        r.name = name;
        r.land = land;
        r.waitTime = stoi(waitStr);
        r.priority = stoi(priorityStr);

        rides.push_back(r);
    }

    file.close();
}

// ================= VIEW =================
void viewRides(const vector<Ride>& rides) {
    cout << "\n===== Available Rides =====\n";

    for (int i = 0; i < rides.size(); i++) {
        cout << i + 1 << ". " << rides[i].name << endl;
        cout << "   Land: " << rides[i].land << endl;
        cout << "   Wait Time: " << rides[i].waitTime << " minutes" << endl;
        cout << "   Priority: " << rides[i].priority << endl;
    }
}

// ================= TOTAL WAIT =================
void showTotalWait(const vector<Ride>& rides) {
    int total = 0;

    for (const Ride& r : rides) {
        total += r.waitTime;
    }

    cout << "\nTotal Wait Time: " << total << " minutes\n";
}

// ================= BEST ORDER =================
void suggestBestOrder(vector<Ride> rides) {
    // Sort by wait time (simple bubble sort for learning)
    for (int i = 0; i < rides.size(); i++) {
        for (int j = i + 1; j < rides.size(); j++) {
            if (rides[j].waitTime < rides[i].waitTime) {
                swap(rides[i], rides[j]);
            }
        }
    }

    cout << "\n===== Suggested Ride Order =====\n";
    for (int i = 0; i < rides.size(); i++) {
        cout << i + 1 << ". " << rides[i].name
            << " - " << rides[i].waitTime << " minutes\n";
    }
}

// ================= UPDATE WAIT =================
void updateWaitTime(vector<Ride>& rides) {
    int choice, newTime;

    viewRides(rides);

    cout << "\nWhich ride would you like to update? ";
    cin >> choice;

    if (choice < 1 || choice > rides.size()) {
        cout << "Invalid choice.\n";
        return;
    }

    cout << "Enter new wait time: ";
    cin >> newTime;

    rides[choice - 1].waitTime = newTime;

    saveRides(rides); // 🔥 SAVE

    cout << "Wait time updated!\n";
}

// ================= UPDATE PRIORITY =================
void updatePriority(vector<Ride>& rides) {
    int choice, newPriority;

    viewRides(rides);

    cout << "\nWhich ride priority do you want to change? ";
    cin >> choice;

    if (choice < 1 || choice > rides.size()) {
        cout << "Invalid choice.\n";
        return;
    }

    cout << "Enter priority (1 = Must Ride, 2 = Nice, 3 = Optional): ";
    cin >> newPriority;

    if (newPriority < 1 || newPriority > 3) {
        cout << "Invalid priority.\n";
        return;
    }

    rides[choice - 1].priority = newPriority;

    saveRides(rides); // 🔥 SAVE

    cout << "Priority updated!\n";
}

// ================= MAIN =================
int main() {
    vector<Ride> rides;

    loadRides(rides);

    // If no file yet → default rides
    if (rides.empty()) {
        rides = {
            {"Star Wars: Rise of the Resistance", "Galaxy's Edge", 75, 1},
            {"Millennium Falcon: Smugglers Run", "Galaxy's Edge", 45, 2}
        };
    }

    int choice;

    do {
        cout << "\n===== Galaxy's Edge Ride Planner =====\n";
        cout << "1. View rides\n";
        cout << "2. Show total wait time\n";
        cout << "3. Suggest best ride order\n";
        cout << "4. Update wait time\n";
        cout << "5. Update priority\n";
        cout << "6. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewRides(rides);
            break;
        case 2:
            showTotalWait(rides);
            break;
        case 3:
            suggestBestOrder(rides);
            break;
        case 4:
            updateWaitTime(rides);
            break;
        case 5:
            updatePriority(rides);
            break;
        case 6:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid option.\n";
        }

    } while (choice != 6);

    return 0;
}
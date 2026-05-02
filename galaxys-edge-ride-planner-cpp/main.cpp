#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Ride {
    string name;
    string land;
    int waitTime;
    int priority;
};

void showMenu();
void viewRides(const vector<Ride>& rides);
void showTotalWaitTime(const vector<Ride>& rides);
void suggestBestOrder(vector<Ride> rides);
void updateWaitTime(vector<Ride>& rides);
void updatePriority(vector<Ride>& rides);
void suggestTimeOfDayStrategy(vector<Ride> rides);
string getPriorityLabel(int priority);

int main() {
    vector<Ride> rides = {
        {"Star Wars: Rise of the Resistance", "Galaxy's Edge", 75, 1},
        {"Millennium Falcon: Smugglers Run", "Galaxy's Edge", 45, 2}
    };

    int choice;

    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            viewRides(rides);
            break;
        case 2:
            showTotalWaitTime(rides);
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
            suggestTimeOfDayStrategy(rides);
            break;
        case 7:
            cout << "May the Force be with you!\n";
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}

void showMenu() {
    cout << "\n===== Galaxy's Edge Ride Planner =====\n";
    cout << "1. View rides\n";
    cout << "2. Show total wait time\n";
    cout << "3. Suggest best ride order\n";
    cout << "4. Update wait time\n";
    cout << "5. Update ride priority\n";
    cout << "6. Time-of-day strategy\n";
    cout << "7. Exit\n";
    cout << "Choose an option: ";
}

void viewRides(const vector<Ride>& rides) {
    cout << "\n===== Available Rides =====\n";

    for (size_t i = 0; i < rides.size(); i++) {
        cout << i + 1 << ". " << rides[i].name << endl;
        cout << "   Land: " << rides[i].land << endl;
        cout << "   Wait Time: " << rides[i].waitTime << " minutes\n";
        cout << "   Priority: " << getPriorityLabel(rides[i].priority) << endl;
    }
}

void showTotalWaitTime(const vector<Ride>& rides) {
    int total = 0;

    for (const Ride& ride : rides) {
        total += ride.waitTime;
    }

    cout << "\nTotal wait time: " << total << " minutes\n";
}

void suggestBestOrder(vector<Ride> rides) {
    sort(rides.begin(), rides.end(), [](const Ride& a, const Ride& b) {
        if (a.priority == b.priority) {
            return a.waitTime < b.waitTime;
        }
        return a.priority < b.priority;
        });

    cout << "\n===== Suggested Ride Order =====\n";

    for (size_t i = 0; i < rides.size(); i++) {
        cout << i + 1 << ". " << rides[i].name
            << " - " << rides[i].waitTime << " minutes"
            << " - " << getPriorityLabel(rides[i].priority) << endl;
    }
}

void updateWaitTime(vector<Ride>& rides) {
    int rideChoice;
    int newWaitTime;

    viewRides(rides);

    cout << "\nWhich ride would you like to update? ";
    cin >> rideChoice;

    if (rideChoice < 1 || rideChoice > static_cast<int>(rides.size())) {
        cout << "Invalid ride selection.\n";
        return;
    }

    cout << "Enter new wait time in minutes: ";
    cin >> newWaitTime;

    rides[rideChoice - 1].waitTime = newWaitTime;

    cout << "Wait time updated successfully.\n";
}

void updatePriority(vector<Ride>& rides) {
    int rideChoice;
    int newPriority;

    viewRides(rides);

    cout << "\nWhich ride would you like to update priority for? ";
    cin >> rideChoice;

    if (rideChoice < 1 || rideChoice > static_cast<int>(rides.size())) {
        cout << "Invalid ride selection.\n";
        return;
    }

    cout << "\nPriority options:\n";
    cout << "1. Must Ride\n";
    cout << "2. Nice to Ride\n";
    cout << "3. Optional\n";
    cout << "Choose priority: ";
    cin >> newPriority;

    if (newPriority < 1 || newPriority > 3) {
        cout << "Invalid priority.\n";
        return;
    }

    rides[rideChoice - 1].priority = newPriority;

    cout << "Priority updated successfully.\n";
}

void suggestTimeOfDayStrategy(vector<Ride> rides) {
    int timeChoice;

    cout << "\n===== Time-of-Day Strategy =====\n";
    cout << "1. Morning\n";
    cout << "2. Afternoon\n";
    cout << "3. Evening\n";
    cout << "Choose time of day: ";
    cin >> timeChoice;

    if (timeChoice == 1) {
        sort(rides.begin(), rides.end(), [](const Ride& a, const Ride& b) {
            if (a.name == "Star Wars: Rise of the Resistance") return true;
            if (b.name == "Star Wars: Rise of the Resistance") return false;
            return a.waitTime < b.waitTime;
            });

        cout << "\nMorning Strategy: Ride Rise of the Resistance early.\n";
    }
    else if (timeChoice == 2) {
        sort(rides.begin(), rides.end(), [](const Ride& a, const Ride& b) {
            return a.waitTime < b.waitTime;
            });

        cout << "\nAfternoon Strategy: Choose the shortest wait first.\n";
    }
    else if (timeChoice == 3) {
        sort(rides.begin(), rides.end(), [](const Ride& a, const Ride& b) {
            if (a.priority == b.priority) {
                return a.waitTime < b.waitTime;
            }
            return a.priority < b.priority;
            });

        cout << "\nEvening Strategy: Prioritize must-ride attractions before park closing.\n";
    }
    else {
        cout << "Invalid time selection.\n";
        return;
    }

    cout << "\n===== Recommended Order =====\n";

    for (size_t i = 0; i < rides.size(); i++) {
        cout << i + 1 << ". " << rides[i].name
            << " - " << rides[i].waitTime << " minutes"
            << " - " << getPriorityLabel(rides[i].priority) << endl;
    }
}

string getPriorityLabel(int priority) {
    switch (priority) {
    case 1:
        return "Must Ride";
    case 2:
        return "Nice to Ride";
    case 3:
        return "Optional";
    default:
        return "Unknown";
    }
}
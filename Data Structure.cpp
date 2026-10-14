// Student Marks Management System
// Real-world application of arrays: storing and processing a class's marks.
// Parallel arrays: names[i] and marks[i] describe the same student (index i).

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

const int MAX_STUDENTS = 50;      // arrays have a fixed size
const double PASS_MARK = 50.0;

string names[MAX_STUDENTS];
double marks[MAX_STUDENTS];
int count = 0;                    // how many slots are actually used

// Helper function to clear invalid inputs from cin
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ---------- Basic operations ----------

void addStudent() {
    if (count >= MAX_STUDENTS) {
        cout << "Array is full. Cannot add more students.\n";
        return;
    }
    cout << "Enter student name: ";
    getline(cin >> ws,names [count]);
    cout << "Enter marks (0-100): ";
    if (!(cin >> marks[count])) {
        cout << "Invalid input type. Student not added.\n";
        clearInput();
        return;
    }
    if (marks[count] < 0 || marks[count] > 100) {
        cout << "Invalid marks range (must be 0-100). Student not added.\n";
        return;
    }
    count++;
    cout << "Student added.\n";
}

void displayAll() {
    if (count == 0) { cout << "No records yet.\n"; return; }
    cout << "\n" << left << setw(5) << "No." << setw(15) << "Name"
         << setw(8) << "Marks" << "Status\n";
    cout << string(36, '-') << "\n";
    for (int i = 0; i < count; i++) {          // O(n) traversal
        cout << left << setw(5) << i + 1 << setw(15) << names[i]
             << setw(8) << fixed << setprecision(1) << marks[i]
             << (marks[i] >= PASS_MARK ? "Pass" : "Fail") << "\n";
    }
}

// ---------- Statistics ----------

void showStatistics() {
    if (count == 0) { cout << "No records yet.\n"; return; }

    double sum = 0, highest = marks[0], lowest = marks[0];
    int hiIdx = 0, loIdx = 0, passed = 0;

    for (int i = 0; i < count; i++) {
        sum += marks[i];
        if (marks[i] > highest) { highest = marks[i]; hiIdx = i; }
        if (marks[i] < lowest)  { lowest = marks[i];  loIdx = i; }
        if (marks[i] >= PASS_MARK) passed++;
    }

    cout << fixed << setprecision(2);
    cout << "\n--- Class Statistics ---\n";
    cout << "Students : " << count << "\n";
    cout << "Average  : " << sum / count << "\n";
    cout << "Highest  : " << highest << " (" << names[hiIdx] << ")\n";
    cout << "Lowest   : " << lowest  << " (" << names[loIdx] << ")\n";
    cout << "Passed   : " << passed << "   Failed: " << count - passed << "\n";
}

// ---------- Searching ----------

void searchStudent() {
    string target;
    cout << "Enter name to search: ";
    cin >> target;
    for (int i = 0; i < count; i++) {          // linear search, O(n)
        if (names[i] == target) {
            cout << "Found at position " << i + 1 << ": " << names[i]
                 << " scored " << marks[i] << "\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

// ---------- Sorting ----------

void sortByMarksDescending() {
    // Bubble sort: swap BOTH arrays so names stay matched with marks.
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (marks[j] < marks[j + 1]) {
                swap(marks[j], marks[j + 1]);
                swap(names[j], names[j + 1]);
            }
        }
    }
    cout << "Sorted by marks (highest first).\n";
    displayAll();
}

// ---------- Updating / deleting ----------

void updateMarks() {
    string target;
    cout << "Enter name to update: ";
    cin >> target;
    for (int i = 0; i < count; i++) {
        if (names[i] == target) {
            double m;
            cout << "Enter new marks: ";
            if (!(cin >> m)) {
                cout << "Invalid input.\n";
                clearInput();
                return;
            }
            if (m < 0 || m > 100) { cout << "Invalid marks.\n"; return; }
            marks[i] = m;                       // O(1) once index is known
            cout << "Updated.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

void deleteStudent() {
    string target;
    cout << "Enter name to delete: ";
    cin >> target;
    for (int i = 0; i < count; i++) {
        if (names[i] == target) {
            // Shift everything after i one place left: O(n)
            for (int j = i; j < count - 1; j++) {
                names[j] = names[j + 1];
                marks[j] = marks[j + 1];
            }
            count--;
            cout << "Deleted.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

// ---------- Menu ----------

int main() {
    int choice;
    do {
        cout << "\n===== STUDENT MARKS SYSTEM =====\n"
             << "1. Add student\n"
             << "2. Display all\n"
             << "3. Class statistics\n"
             << "4. Search by name\n"
             << "5. Sort by marks\n"
             << "6. Update marks\n"
             << "7. Delete student\n"
             << "0. Exit\n"
             << "Choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid choice! Please enter a number.\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1: addStudent();          break;
            case 2: displayAll();          break;
            case 3: showStatistics();      break;
            case 4: searchStudent();       break;
            case 5: sortByMarksDescending(); break;
            case 6: updateMarks();         break;
            case 7: deleteStudent();       break;
            case 0: cout << "Goodbye!\n";  break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}

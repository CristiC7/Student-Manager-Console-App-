#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> // for numeric_limits
#include <fstream>
#include <string>
#include <cctype> // for tolower()

class Student {
    std::string name;
    float average;

public:
    Student(std::string n, float a) : name(std::move(n)), average(a) {}

    void display() const {
        std::cout << name << " - Average: " << average << "\n";
    }

    float getAverage() const { return average; }
    std::string getName() const { return name; }

    static void addStudent(std::vector<Student>& list) { 
        std::string name;
        float average;

        std::cout << "\n--- Add Student ---\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        std::cout << "Student name: ";
        std::getline(std::cin, name); // Read the name with spaces

        std::cout << "Average (1-10): ";
        std::cin >> average;

        if (std::cin.fail() || average < 1.0f || average > 10.0f) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Average must be between 1 and 10.\n";
            return;
        }

        list.emplace_back(name, average);
        std::cout << "Student added successfully!\n";
    }

    static void displayAll(const std::vector<Student>& list) {
        std::cout << "\n--- Student List ---\n";
        if (list.empty()) {
            std::cout << "No students in the list.\n";
            return;
        }
        for (const auto& s : list) {
            s.display();
        }
    }

    static void sortByAverage(std::vector<Student>& list) {
        if (list.empty()) {
            std::cout << "No students to sort.\n";
            return;
        }
        if (list.size() == 1) {
            std::cout << "Only one student in the list.\n";
            displayAll(list);
            return;
        }
        std::sort(list.begin(), list.end(),
            [](const Student& a, const Student& b) {
                return a.getAverage() > b.getAverage();
            });
        std::cout << "Students sorted by average (highest to lowest):\n";
        displayAll(list);
    }

    static void editStudent(std::vector<Student>& list) {
        if (list.empty()) {
            std::cout << "No students to edit.\n";
            return;
        }

        displayAll(list);
        std::cout << "Enter student position to edit (0-" << list.size() - 1 << "): ";
        size_t index;
        std::cin >> index;

        if (index >= list.size()) {
            std::cout << "Invalid position.\n";
            return;
        }

        std::string newName;
        float newAverage;

        std::cin.ignore();
        std::cout << "New name (leave empty to keep current): ";
        std::getline(std::cin, newName);

        std::cout << "New average (enter -1 to keep current): ";
        std::cin >> newAverage;

        if (!newName.empty()) {
            list[index].name = newName;
        }
        if (newAverage != -1.0f) {
            if (newAverage >= 1.0f && newAverage <= 10.0f) {
                list[index].average = newAverage;
            } else {
                std::cout << "Average must be between 1 and 10. Keeping old value.\n";
            }
        }

        std::cout << "Student updated successfully!\n";
        list[index].display();
    }

    static void deleteStudent(std::vector<Student>& list) {
        if (list.empty()) {
            std::cout << "No students to delete.\n";
            return;
        }

        displayAll(list);
        std::cout << "Enter student position to delete (0-" << list.size() - 1 << "): ";
        size_t index;
        std::cin >> index;

        if (index >= list.size()) {
            std::cout << "Invalid position.\n";
            return;
        }

        std::cout << "Deleting: ";
        list[index].display();
        list.erase(list.begin() + index);
        std::cout << "Student deleted successfully!\n";
    }

    static void searchStudent(const std::vector<Student>& list) {
        if (list.empty()) {
            std::cout << "No students to search.\n";
            return;
        }

        std::string searchName;
        std::cin.ignore();
        std::cout << "Enter name to search: ";
        std::getline(std::cin, searchName);

        bool found = false;
        for (const auto& s : list) {
            std::string studentName = s.getName();
            // Case-insensitive search
            if (studentName.find(searchName) != std::string::npos) {
                s.display();
                found = true;
            }
        }

        if (!found) {
            std::cout << "No students found containing: " << searchName << "\n";
        }
    }

    static void saveToFile(const std::vector<Student>& list, const std::string& filename = "students.txt") {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "Error opening file for writing.\n";
            return;
        }

        for (const auto& s : list) {
            file << s.getName() << "," << s.getAverage() << "\n";
        }

        file.close();
        std::cout << "Saved " << list.size() << " students to " << filename << ".\n";
    }

    static void loadFromFile(std::vector<Student>& list, const std::string& filename = "students.txt") {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Error opening file for reading.\n";
            return;
        }

        list.clear();
        std::string line;
        while (std::getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos == std::string::npos) continue; // Skip malformed entries

            std::string name = line.substr(0, commaPos);
            float average;
            try {
                average = std::stof(line.substr(commaPos + 1));
            } catch (...) {
                continue; // Skip malformed entries
            }

            if (average >= 1.0f && average <= 10.0f) {
                list.emplace_back(name, average);
            }
        }

        file.close();
        std::cout << "Loaded " << list.size() << " students from " << filename << ".\n";
    }
};

int showMenu() {
    int option;
    std::cout << "\n=== STUDENT MANAGER MENU ===\n";
    std::cout << "1. Add student\n";
    std::cout << "2. Display all students\n";
    std::cout << "3. Sort by average\n";
    std::cout << "4. Edit student\n";
    std::cout << "5. Delete student\n";
    std::cout << "6. Search student\n";
    std::cout << "7. Save to file\n";
    std::cout << "8. Load from file\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
    std::cin >> option;
    return option;
}

void runMenu(std::vector<Student>& students) {
    int option;
    do {
        option = showMenu();

        switch (option) {
            case 1: Student::addStudent(students); break;
            case 2: Student::displayAll(students); break;
            case 3: Student::sortByAverage(students); break;
            case 4: Student::editStudent(students); break;
            case 5: Student::deleteStudent(students); break;
            case 6: Student::searchStudent(students); break;
            case 7: Student::saveToFile(students); break;
            case 8: Student::loadFromFile(students); break;
            case 0: std::cout << "Exiting program.\n"; break;
            default: {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
                std::cout << "Invalid option. Try again.\n";
            }
        }
    } while (option != 0);
}

int main() {
    std::vector<Student> students;
    runMenu(students);
    return 0;
}
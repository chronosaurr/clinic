#include "menu.h"
#include <iostream>

Menu::Menu() {
    // Dodajmy przykładowych pacjentów do testów
    patients.push_back({"Anna", "Kowalska", "12345678901"});
    patients.push_back({"Jan", "Nowak", "98765432101"});
}

void Menu::display() const {
    int choice;
    do {
        std::cout << R"(
=== Clinic Database Menu ===
 1. Display all patients
 2. Display visits for a patient
 3. Add a new patient
 4. Edit patient details
 5. Add a visit
 6. Import data
 0 - Exit
Select an option: )";
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayPatients();
            break;
            case 0:
                std::cout << "Exiting application.\n";
            break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 0);
}

void Menu::displayPatients() const {
    if (patients.empty()) {
        std::cout << "No patients found.\n";
        return;
    }

    std::cout << "\n=== List of Patients ===\n";
    for (const auto& patient : patients) {
        std::cout << "Name: " << patient.firstName << " " << patient.lastName
                  << ", PESEL: " << patient.pesel << "\n";
    }
}
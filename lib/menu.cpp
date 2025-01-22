#include "menu.h"
#include "engine.h"
#include <iostream>

Menu::Menu(Engine& eng) : engine(eng) {}

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
Select an option:
)";
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayPatients();
            break;
            case 3:
                addNewPatient();
            break;
            case 4:
                engine.addVisit();
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
    const auto& patients = engine.getPatients();

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

void Menu::addNewPatient() const {
    Patient patient;

    std::cout << "Enter first name: ";
    std::cin >> patient.firstName;

    std::cout << "Enter last name: ";
    std::cin >> patient.lastName;

    std::cout << "Enter PESEL: ";
    std::cin >> patient.pesel;

    engine.addPatient(patient);
    engine.savePatientsToFile("database.json");
}



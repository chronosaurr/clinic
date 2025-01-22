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
 4. Add a visit for a patient
 0 - Exit
Select an option:
)";
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayPatients();
            break;
            case 2:
                displayVisits();
            break;
            case 3:
                addNewPatient();
            break;
            case 4:
                addNewVisit();
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

void Menu::addNewVisit() const {
    std::string pesel;
    std::cout << "Enter PESEL of the patient: ";
    std::cin >> pesel;

    const auto& patients = engine.getPatients();
    auto it = std::find_if(patients.begin(), patients.end(), [&pesel](const Patient& patient) {
        return patient.pesel == pesel;
    });

    if (it == patients.end()) {
        std::cout << "Patient with PESEL " << pesel << " not found.\n";
        return;
    }

    Visit visit;
    std::cout << "Enter visit date (YYYY-MM-DD): ";
    std::cin >> visit.date;

    std::cout << "Enter diagnosis: ";
    std::cin.ignore(); // Ignoring leftover newline character
    std::getline(std::cin, visit.diagnosis);

    engine.addVisit(pesel, visit);
    engine.savePatientsToFile("database.json");
}

void Menu::displayVisits() const {
    std::string pesel;
    std::cout << "Enter the PESEL of the patient: ";
    std::cin >> pesel;

    const auto& visits = engine.getVisits(pesel);

    if (visits.empty()) {
        std::cout << "No visits found for patient with PESEL " << pesel << ".\n";
        return;
    }

    std::cout << "\n=== Visits for PESEL: " << pesel << " ===\n";
    for (const auto& visit : visits) {
        std::cout << "Date: " << visit.date << ", Diagnosis: " << visit.diagnosis << "\n";
    }
}

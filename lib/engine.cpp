#include "engine.h"
#include <iostream>
#include <fstream>

void Engine::loadPatientsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return;
    }

    nlohmann::json jsonData;
    try {
        file >> jsonData;
        for (const auto& item : jsonData["patients"]) {
            Patient patient;
            patient.firstName = item["firstName"].get<std::string>();
            patient.lastName = item["lastName"].get<std::string>();
            patient.pesel = item["pesel"].get<std::string>();
            patients.push_back(patient);
        }
        std::cout << "Patients loaded successfully from " << filename << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON file: " << e.what() << "\n";
    }
}

void Engine::savePatientsToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
        return;
    }

    nlohmann::json jsonData;
    jsonData["patients"] = nlohmann::json::array();

    for (const auto& patient : patients) {
        jsonData["patients"].push_back({
            {"firstName", patient.firstName},
            {"lastName", patient.lastName},
            {"pesel", patient.pesel}
        });
    }

    try {
        file << jsonData.dump(4); // Zapis z wcięciem 4 spacji
        std::cout << "Patients saved successfully to " << filename << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error writing to JSON file: " << e.what() << "\n";
    }
}

const std::vector<Patient>& Engine::getPatients() const {
    return patients;
}

void Engine::addPatient(const Patient& patient) {
    for (const auto& existingPatient : patients) {
        if (existingPatient.pesel == patient.pesel) {
            std::cerr << "Patient with this PESEL " << patient.pesel << " already exists in our database.\n";
            return;
        }
    }
    patients.push_back(patient);
    std::cout << "Patient " << patient.firstName << " " << patient.lastName << " added successfully.\n";
}

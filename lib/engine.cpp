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

const std::vector<Patient>& Engine::getPatients() const {
    return patients;
}

#include "engine.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

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

            // Odczyt wizyt (jeśli istnieją)
            if (item.contains("visits")) {
                for (const auto& visitItem : item["visits"]) {
                    Visit visit;
                    visit.date = visitItem["date"].get<std::string>();
                    visit.diagnosis = visitItem["diagnosis"].get<std::string>();
                    visits[patient.pesel].push_back(visit);
                }
            }
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
        nlohmann::json patientData = {
            {"firstName", patient.firstName},
            {"lastName", patient.lastName},
            {"pesel", patient.pesel},
            {"visits", nlohmann::json::array()}
        };

        // Dodanie wizyt do pacjenta
        if (visits.find(patient.pesel) != visits.end()) {
            for (const auto& visit : visits.at(patient.pesel)) {
                patientData["visits"].push_back({
                    {"date", visit.date},
                    {"diagnosis", visit.diagnosis}
                });
            }
        }

        jsonData["patients"].push_back(patientData);
    }
    try {
        file << jsonData.dump(4); // Zapis z wcięciem 4 spacji
        std::cout << "Patients and visits saved successfully to " << filename << "\n";
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

void Engine::addVisit(const std::string& pesel, const Visit& visit) {
    auto it = std::find_if(patients.begin(), patients.end(), [&pesel](const Patient& patient) {
        return patient.pesel == pesel;
    });

    if (it == patients.end()) {
        std::cerr << "Patient with PESEL " << pesel << " not found.\n";
        return;
    }

    visits[pesel].push_back(visit);
    std::cout << "Visit added for patient with PESEL " << pesel << ".\n";
}

const std::vector<Visit>& Engine::getVisits(const std::string& pesel) const {
    static const std::vector<Visit> emptyVisits;
    auto it = visits.find(pesel);
    if (it != visits.end()) {
        return it->second;
    }
    return emptyVisits;
}

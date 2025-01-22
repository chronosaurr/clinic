#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

struct Patient {
    std::string firstName;
    std::string lastName;
    std::string pesel;
};

struct Visit {
    std::string date;
    std::string diagnosis;
};

class Engine {
private:
    std::vector<Patient> patients; // Patient list
    std::unordered_map<std::string, std::vector<Visit>> visits; // Mapowanie PESEL -> Visits

public:
    // patients and all about em
    void loadPatientsFromFile(const std::string& filename); // Reading patient list from JSON file
    void savePatientsToFile(const std::string& filename) const; // Saving patients to JSON file
    const std::vector<Patient>& getPatients() const; // Gives back the patient list
    void addPatient(const Patient& patient); // Adding new patients

    // visits and all about em
    void addVisit(const std::string& pesel, const Visit& visit); // Adding new visits to a patient
    const std::vector<Visit>& getVisits(const std::string& pesel) const; // Gives back visits of a patient
};

#endif // ENGINE_H

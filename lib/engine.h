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
    std::vector<Patient> patients; // Lista pacjentów
    std::unordered_map<std::string, std::vector<Visit>> visits; // Mapowanie PESEL -> Wizyty

public:

    // Pacjenci co i jak
    void loadPatientsFromFile(const std::string& filename); // Odczyt pacjentów z pliku JSON
    void savePatientsToFile(const std::string& filename) const; // Zapis pacjentów do pliku JSON
    const std::vector<Patient>& getPatients() const; // Zwraca listę pacjentów
    void addPatient(const Patient& patient); // Dodawanie nowego pacjenta

    // Wizyty co i jak
    void addVisit(const std::string& pesel, const Visit& visit); // Dodawanie wizyty dla pacjenta
    const std::vector<Visit>& getVisits(const std::string& pesel) const; // Pobranie wizyt pacjenta
};

#endif // ENGINE_H

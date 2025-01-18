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

class Engine {
private:
    std::vector<Patient> patients; // Lista pacjentów

public:
    void loadPatientsFromFile(const std::string& filename); // Odczyt pacjentów z pliku JSON
    const std::vector<Patient>& getPatients() const; // Zwraca listę pacjentów
};

#endif // ENGINE_H

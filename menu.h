#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

struct Patient {
    std::string firstName;
    std::string lastName;
    std::string pesel;
};

class Menu {
private:
    std::vector<Patient> patients; // Lista pacjentów w pamięci

    void displayPatients() const; // Wyświetlenie listy pacjentów

public:
    Menu();
    void display() const; // Główne menu
};

#endif // MENU_H
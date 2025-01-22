#ifndef MENU_H
#define MENU_H

#include "engine.h"

class Menu {
private:
    Engine& engine; // Ref do silnika aplikacji

    void displayPatients() const; // Wyświetlenie listy pacjentów
    void addNewPatient() const; // adding a new patient

public:
    explicit Menu(Engine& eng);

    void display() const;

};

#endif // MENU_H

#ifndef MENU_H
#define MENU_H

#include "engine.h"

class Menu {
private:
    Engine& engine; // Referencja do silnika aplikacji

    void displayPatients() const; // Wyświetlenie listy pacjentów

public:
    explicit Menu(Engine& eng);

    void display() const;

};

#endif // MENU_H

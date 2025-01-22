#include <iostream>
#include "lib/menu.h"
#include "lib/engine.h"

// Baza danych przychodni
// Przechowywanie skończonej liczby pacjentów i ich danych (imię, nazwisko, PESEL itd.).
// Każdy pacjent ma swoją historię wizyt (data, rozpoznanie), którą można przeglądać.
// Możliwość dodawania nowych wizyt.


// jak nie dziala 1 to sprawdzic czy run>edit configuration jest ustawione na dobrym working directory!!!

int main() {
    Engine engine; // Tworzymy instancję Engine
    engine.loadPatientsFromFile("database.json"); // Ładowanie danych z pliku JSON

    Menu menu(engine); // Tworzymy instancję Menu, przekazując Engine jako argument
    menu.display(); // Wyświetlamy menu

    return 0;
}
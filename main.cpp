#include "lib/menu.h"
#include "lib/engine.h"

// jak nie dziala 1 to sprawdzic czy run>edit configuration jest ustawione na dobrym working directory!!!

int main() {
    Engine engine; // creating "Engine"
    engine.loadPatientsFromFile("database.json"); // loading data from file JSON

    Menu menu(engine); // creating "Menu" and having "Engine" as an argument
    menu.display(); // printing menu

    return 0;
}

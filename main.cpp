#include <iostream>
#include "menu.h"


// Baza danych przychodni
// Przechowywanie skończonej liczby pacjentów i ich danych (imię, nazwisko, PESEL itd.).
// Każdy pacjent ma swoją historię wizyt (data, rozpoznanie), którą można przeglądać.
// Możliwość dodawania nowych wizyt.


int main(){
    Menu menu;
    menu.display();
    return 0;
}

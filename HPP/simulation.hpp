#ifndef SIMULATION_H
#define SIMULATION_H

#include <fstream>
#include "functions.hpp"
#include "country.hpp"

void Game(const list<string> countryNames, list<int> population) {
    list<Country> countries; // create all countries
    for(int i = 0; i < countryNames.size(); i++) {
        Country country(get(countryNames, i), get(population, i));
        countries.push_back(country);
    }
    const Country groundZero = get(countries, rand_int(1, countries.size())); // pick a random country
    cout << groundZero.name;
}

int menu_screen() {
    ifstream menuScreenInfo;
    open_file(menuScreenInfo, "Data/menuscreeninfo.txt");
    print(read_ifstream_to_list(menuScreenInfo, 1, ','));
    const int menuOption = get_user_input(1, 3);
    switch(menuOption) {
        case 1: {
            return 1;
        }
        case 2: {
            ifstream menuScreenInfo;
            open_file(menuScreenInfo, "Data/credits.txt");
            print(read_ifstream_to_list(menuScreenInfo, 1, ','));
            char waitForUser[] = "";
            cin >> waitForUser;            
            menu_screen();
            return -1;
        }
        case 3: {
            return -1;
        }
    }
}



#endif
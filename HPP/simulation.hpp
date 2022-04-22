#ifndef SIMULATION_H
#define SIMULATION_H

#include <fstream>
#include "functions.hpp"
#include "country.hpp"

void Game(const list<string> countryNames, list<int> population) {
    list<Country> untouched; // create all countries
    list<Country> infected;
    for(int i = 0; i < countryNames.size(); i++) {
        Country country(get(countryNames, i), get(population, i));
        untouched.push_back(country);
    }

    const Country groundZero = get(untouched, rand_int(1, untouched.size())); // pick a random country
    untouched.remove(groundZero);
    cout << "Ground Zero is " << groundZero.name << " with a population of " << groundZero.get_population() << endl;
    
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
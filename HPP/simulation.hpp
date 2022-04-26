#ifndef SIMULATION_H
#define SIMULATION_H

#include <fstream>

#include "functions.hpp"
#include "country.hpp"

void Simulate(const list<string> countryNames, list<int> population) {
    clear_screen();
    list<Country> untouched; // create all countries
    list<Country> infectedCountries;
    int totalInfected = 1;
    const long int WORLD_POPULATION = 7808449406;
    int day;

    for(int i = 0; i < countryNames.size(); i++) {
        Country country(get(countryNames, i), get(population, i));
        untouched.push_back(country);
    }

    Country groundZero = get(untouched, rand_int(1, untouched.size())); // pick a random country
    groundZero.infect();
    untouched.remove(groundZero);
    infectedCountries.push_back(groundZero);
    cout << "The first country to become infected is '" << groundZero.name << "' with a population of " << groundZero.get_population() << endl;
    cout << "Press enter to continue." << endl;
    wait_for_enter();
    clear_screen();
    while(totalInfected != WORLD_POPULATION) {
        clear_screen();
        cout << "Day: " << day << endl;
        day++;
        for(int i = 0; i < infectedCountries.size(); i++) {
            Country current = get(infectedCountries, i);
            infectedCountries.remove(current);
            current.new_day(totalInfected, untouched, infectedCountries);
            current.print_info();
            infectedCountries.push_back(current);
        }
        wait_for_enter(false);
    }

}

int menu_screen() {
    clear_screen();
    ifstream menuScreenInfo;
    open_file(menuScreenInfo, "Data/menuscreeninfo.txt");
    print(read_ifstream_to_list(menuScreenInfo, 1, ','));
    const int menuOption = get_user_input(1, 3);
    switch(menuOption) {
        case 1: {
            return 1;
        }
        case 2: {
            clear_screen();
            ifstream menuScreenInfo;
            open_file(menuScreenInfo, "Data/credits.txt");
            print(read_ifstream_to_list(menuScreenInfo, 1, ','));
            wait_for_enter();
            menu_screen();
            return -1;
        }
        case 3: {
            return -1;
        }
    }
}



#endif
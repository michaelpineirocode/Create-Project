#ifndef SIMULATION_H
#define SIMULATION_H

#include <fstream>

#include "functions.hpp"
#include "country.hpp"

/**
 * @brief The main simulation function that does start up and holds the while loop
 * 
 * @param countryNames a list of all country names
 * @param population  a list of the population of each country, where each element's index coresponds with countryNames
 */
void Simulate(const list<string> countryNames, list<int> population) {
    // set up the simulation!
    clear_screen();

    list<Country> untouched; // create all countries
    list<Country> infectedCountries;
    list<Country> overtaken;
    long long int totalInfected = 1;
    const long long int WORLD_POPULATION = 7808449172;
    int day = 1;
    int lastID = 1;
    bool skip = false;
    // all the countries start untouched
    for(int i = 0; i < countryNames.size(); i++) {
        Country country(get(countryNames, i), get(population, i));
        untouched.push_back(country);
    }

    // create a ground zero!
    Country groundZero = get(untouched, rand_int(0, untouched.size())); // pick a random country
    groundZero.infect();
    groundZero.id = lastID;
    untouched.remove(groundZero);
    infectedCountries.push_back(groundZero);

    cout << "The first country to become infected is '" << groundZero.name << "' with a population of " << groundZero.get_population() << endl;
    cout << "Press enter to continue." << endl;
    wait_for_enter();
    clear_screen();

    // start the while loop to the simulatioN!
    while(true) {
        // all the screen output
        clear_screen();
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << "Day: " << day << endl;
        cout << "Infected: " << totalInfected << endl;
        cout << "World population: " << WORLD_POPULATION << endl;
        cout << "Infected countries: " << infectedCountries.size() << endl;
        cout << "Overtaken countries: " << overtaken.size() << endl;
        cout << "Untouched countries: " << untouched.size() << endl;
        day++;
        // base case to end the simulation
        if(totalInfected >= WORLD_POPULATION) {
            cout << "The entire world has been infected in " << day - 1 << " days!" << endl;
            cout << "Press enter to continue" << endl;
            wait_for_enter(false);
            return;
        }

        // resort the list to always output in the right order
        infectedCountries = mergeSort(infectedCountries);

        // print every infected and overtaken country
        if(!skip) {
            cout << "Type 'skip' at any time to continue the simulation without pressing enter." << endl;
            // print all overtaken countries
            if(overtaken.size() != 0) {
                cout << "Overtaken countries: " << "                 Note: overtaken countries can still spread!" << endl;
                for(int i = 0; i < overtaken.size(); i++) {
                    cout << '\t' << get(overtaken, i).name << endl;
                }
            cout << endl;
            } // print the info of all infected countries
            for(int i = 0; i < infectedCountries.size(); i++) {
                Country current = get(infectedCountries, i);
                current.print_info();
            }
        }

        // a new day for each country still being infected
        for(int i = 0; i < infectedCountries.size(); i++) {
            Country current = get(infectedCountries, i);
            infectedCountries.remove(current); // remove from list so it can be updated and added back later
            current.new_day(totalInfected, untouched, infectedCountries, lastID); // update country info
            if(current.get_infect_rate() != 1000) {
                infectedCountries.push_front(current); // continue pushing to front if not fully infected
            } else if(current.overtaken) { // add to overtaken  
                overtaken.push_back(current);
            }
        }
        // continue attempting to spread for countries that have been overtaken
        if(untouched.size() > 0) {
            for(int i = 0; i < overtaken.size(); i++) {
                Country current = get(overtaken, i);
                current.spread(untouched, infectedCountries, lastID);
            }
        }

        // get user input and check for quit, skip, or ok command
        if(!skip) {
            const int INPUT = wait_for_enter(false);
            switch(INPUT) {
                case -1: {
                    return; // quit command
                }
                case 1: {
                    skip = true; // skip command
                }
            }
        }
    }
    return;
}

/**
 * @brief displays the main menu and contains logic for what do do if the user presses a corresponding button
 * 
 * @return int corresponding to whether to return to menuScreen again or start simulation
 */
int menu_screen() {
    clear_screen(); // clear the screen
    ifstream menuScreenInfo;
    if(!open_file(menuScreenInfo, "Data/menuscreeninfo.txt")) {
        cout << "Error opening menu screen." << endl;
        return -1;
    }
    print(read_ifstream_to_list(menuScreenInfo, 1, ',')); // print the menu screen
    const int menuOption = get_user_input(1, 4); // get user input
    switch(menuOption) {
        case 1: {
            return 1; // start game
        }
        case 2: {
            print_file_to_screen("Data/credits.txt"); // read credits
            menu_screen(); // recursively call the menu screen
            return -1;
        }
        case 3: {
            print_file_to_screen("Data/howtoplay.txt"); // read howtoplay
            menu_screen(); // recursively call menu screen
            return -1;
        }
        case 4: {
            return -1; // return with -1 to quit
        }
    }
    return 0; // this will never happen but is put to avoid warning
}



#endif
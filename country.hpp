#ifndef COUNTRY_H
#define COUNTRY_H

#include <iostream>
#include <list>
#include <string>
#include "virus.hpp"

using namespace std;

class Country {
    public:
        // constructors!
        Country(const string NAME, const int POPULATION);
        Country(const string NAME, const int POPULATION, const int INFECTED, const int VACCINATED);
        // public attributes
        string name;
        // public operations
        void new_day(int& total_infected, list<Country>& untouched, list<Country>& infectedCountry);

        // getters!
        void print_info();
        int get_population();
        int get_infected();
        int get_infect_rate();
        int get_spread_rate();
        int get_vaccinated();

    private:
        // private attributes
        int population;
        int infected;
        int infectRate;
        int spreadRate;
        int vaccinated;

};

void Country::new_day(int& totalInfected, list<Country>& untouched, list<Country>& infectedCountry) {
    infect(infectRate, infected, totalInfected);
    update_infectRate(population, infected, infectRate);
    update_spreadRate(infectRate, spreadRate);
    spread(untouched, infectedCountry, spreadRate);

}

void Country::print_info() {
    cout << name << ":" << endl;
    cout << "\t" << "Population: " << population << endl;
    cout << "\t" << "Infected: " << infected << endl;
    cout << "\t" << "Vaccinated: " << vaccinated << endl;
    cout << "\t" << "Infection Rate: " << "(" << infectRate << " / 1000) people per day" << endl;
    cout << "\t" << "Chance of Spreading: " << spreadRate << "%" << endl;

}

int Country::get_population() {
    return population;
}

int Country::get_infected() {
    return infected;
}

int Country::get_infect_rate() {
    return infectRate;
}

int Country::get_spread_rate() {
    return spreadRate;
}

int Country::get_vaccinated() {
    return vaccinated;
}


#endif
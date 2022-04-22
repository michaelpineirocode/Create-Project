#ifndef COUNTRY_H
#define COUNTRY_H

#include <iostream>
#include <list>
#include <string>
#include <math.h>

#include "functions.hpp"

using namespace std;

class Country {
    public:
        // constructors!
        Country(const string NAME, const int POPULATION);
        Country(const string NAME, const int POPULATION, const int INFECTED, const int VACCINATED);
        Country& operator=(const Country& OTHER);
        ~Country();
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

        Country get(list<Country> list1, const int INDEX);

    private:
        // private attributes
        int population;
        int infected;
        int infectRate;
        int spreadRate;
        int vaccinated;

        void infect(const int infectRate, int& infected, int& totalInfected);
        void update_infectRate(const int population, const int infected, int& infectRate);
        void update_spreadRate(const int infectRate, int& spreadRate);
        void spread(list<Country>& untouched, list<Country>& infectedCountry, int spreadRate);
        void spreadToCountry(list<Country>& infected, list<Country>& untouched);

};


Country::Country(const string NAME, const int POPULATION) {
    name = NAME;
    population = POPULATION;
    infected = 0;
    infectRate = 0;
    spreadRate = 0;
    vaccinated = 0;
}

Country::Country(const string NAME, const int POPULATION, const int INFECTED, const int VACCINATED) {
    name = NAME;
    population = POPULATION;
    infected = INFECTED;
    vaccinated = VACCINATED;
    infectRate = 0;
    spreadRate = 0;
    vaccinated = 0;
}

Country& Country::operator=(const Country& OTHER) {
    if(this == &OTHER) {
        return * this;
    }
    this->name = OTHER.name;
    this->infected = OTHER.infected;
    this->infectRate = OTHER.infectRate;
    this->spreadRate = OTHER.spreadRate;
    this->vaccinated = OTHER.vaccinated;
    return *this;
}

bool operator==(const Country& COUNTRY, const Country& OTHER) {
    if(COUNTRY.name == OTHER.name) {
        return true;
    } else {
        return false;
    }
}

Country::~Country() = default;

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

void Country::update_infectRate(const int POPULATION, const int INFECTED, int& infectRate) {
    //const int CONT_FACTOR = ceil(double(1/1000) / (1 / POPULATION)) ; // helps smooth scaling between different populations
    //infectRate = (double(INFECTED) / POPULATION) * CONT_FACTOR;
    infectRate = ceil((INFECTED / POPULATION) * 1000);
}

void Country::update_spreadRate(const int infectRate, int& spreadRate) {
    spreadRate = infectRate / 100;
}

void Country::spread(list<Country>& untouched, list<Country>& infected, const int spreadRate) {
    if(rand_int(0, 1001) < spreadRate) {
        spreadToCountry(infected, untouched);
    }
}

void Country::infect(const int infectRate, int& infected, int& totalInfected) {
    for(int i = 0; i < infected; i ++) { // for each infected person
        int ODDS = rand_int(0, 1001);
        if(ODDS < infectRate) {
            infected++;
            totalInfected++;
        }
    }
}

void Country::spreadToCountry(list<Country>& infected, list<Country>& untouched) {
    if(untouched.size() == 0) {
        return;
    } else {
        Country infectedCountry = get(untouched, rand_int(0, untouched.size() - 1));
        infected.push_back(infectedCountry);
        untouched.remove(infectedCountry);
    }
}

Country Country::get(list<Country> list1, const int INDEX) {
    typename list<Country>::iterator it;
    it = list1.begin();
    advance(it, INDEX);
    return *it;
}

#endif
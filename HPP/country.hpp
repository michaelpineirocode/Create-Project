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
        Country(const string NAME, const int POPULATION, const int INFECTED, const int ID);
        Country& operator=(const Country& OTHER);
        ~Country();
        
        // public attributes
        string name;
        int id;
        bool overtaken = false;
        bool canSpread = true;
        
        // public operations
        void new_day(long int& totalInfected, list<Country>& untouched, list<Country>& infectedCountry,  int& lastID);
        void spread(list<Country>& untouched, list<Country>& infectedCountry, int& lastID);
        void infect();

        // getters!
        void print_info();
        int get_population() const;
        int get_infected() const;
        int get_infect_rate() const;
        int get_spread_rate() const;

        Country get(list<Country> list1, const int INDEX);

    private:
        // private attributes
        int population;
        int infected;
        int infectRate;
        int spreadRate;

        // private operations
        void infect(long int& totalInfected);
        void update_infectRate(list<Country>& infectedCountry);
        void update_spreadRate();

};


Country::Country(const string NAME, const int POPULATION) {
    name = NAME;
    population = POPULATION;
    infected = 0;
    infectRate = 0;
    spreadRate = 0;
}

Country::Country(const string NAME, const int POPULATION, const int INFECTED, const int ID) {
    name = NAME;
    population = POPULATION;
    infected = INFECTED;
    infectRate = 0;
    spreadRate = 0;
    id = ID;
}

Country& Country::operator=(const Country& OTHER) {
    if(this == &OTHER) {
        return * this;
    }
    this->name = OTHER.name;
    this->infected = OTHER.infected;
    this->infectRate = OTHER.infectRate;
    this->spreadRate = OTHER.spreadRate;
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

void Country::new_day(long int& totalInfected, list<Country>& untouched, list<Country>& infectedCountry, int& lastID) {
    update_infectRate(infectedCountry);
    update_spreadRate();
    infect(totalInfected);
    spread(untouched, infectedCountry, lastID);

}

void Country::print_info() {
    cout << name << ":" << endl;
    cout << "\t" << "Population: " << population << endl;
    cout << "\t" << "Infected: " << infected << endl;
    cout << "\t" << "Infection Rate: " << "(" << infectRate << " / 1000) people per day" << endl;
    cout << "\t" << "Chance of Spreading: " << spreadRate << endl;

}

int Country::get_population() const{
    return population;
}

int Country::get_infected() const{
    return infected;
}

int Country::get_infect_rate() const{
    return infectRate;
}

int Country::get_spread_rate() const{
    return spreadRate;
}

void Country::update_infectRate(list<Country>& infectedCountry) {
    //const int CONT_FACTOR = ceil(double(1/1000) / (1 / POPULATION)) ; // helps smooth scaling between different populations
    //infectRate = (double(INFECTED) / POPULATION) * CONT_FACTOR;
    if(infectRate < 1000) {
        infectRate = infectRate + ((double)infected / population) * 1000;
        //cout << infectRate << endl;
        if(rand_int(1, 3) == 2) { // gets the game started and keeps the game moving at a reasonable rate
            infectRate++;
        }
        if(infectRate > 1000) {
            infectRate = 1000;
            overtaken = true;
        }
    }
}

void Country::update_spreadRate() {
    spreadRate = infectRate / 100;
}

void Country::spread(list<Country>& untouched, list<Country>& infected, int& lastID) {
    if(rand_int(0, 1001) < spreadRate) {
        if(untouched.size() == 0) {
            return;
        } else {
            Country infectedCountry = get(untouched, rand_int(0, untouched.size() - 1));
            infectedCountry.infect();
            infectedCountry.id = ++lastID;
            infected.push_back(infectedCountry);
            untouched.remove(infectedCountry);
        }
    }
}

void Country::infect(long int& totalInfected) {
    for(int i = 0; i < infected; i ++) { // for each infected person
        int ODDS = rand_int(0, 1001);
        if((ODDS <= infectRate) && (infected < population)) {
            infected++;
            totalInfected++;
        }
    }
}

void Country::infect() {
    if(infected == 0) {
        infected++;
    }
}

Country Country::get(list<Country> list1, const int INDEX) {
    typename list<Country>::iterator it;
    it = list1.begin();
    advance(it, INDEX);
    return *it;
}

#endif
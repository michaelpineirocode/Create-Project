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
        Country(const string NAME, const long long int POPULATION);
        Country& operator=(const Country& OTHER);
        ~Country();
        
        // public attributes
        string name = "NONE";
        int id;
        bool overtaken = false;
        bool canSpread = true;
        
        // public operations
        void new_day(long long int& totalInfected, list<Country>& untouched, list<Country>& infectedCountry,  int& lastID);
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
        long long int population;
        int infected;
        int infectRate;
        int spreadRate;

        // private operations
        void infect(long long int& totalInfected);
        void update_infectRate();
        void update_spreadRate();

};


Country::Country(const string NAME, const long long int POPULATION) {
    name = NAME;
    population = POPULATION;
    infected = 0;
    infectRate = 0;
    spreadRate = 0;
}

Country& Country::operator=(const Country& OTHER) {
    if(this == &OTHER) {
        return *this;
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

void Country::new_day(long long int& totalInfected, list<Country>& untouched, list<Country>& infectedCountry, int& lastID) {
    update_infectRate();
    infect(totalInfected);
    if(untouched.size() > 0) {
        spread(untouched, infectedCountry, lastID);
        update_spreadRate();
    }
}

/**
 * @brief print the info of the country
 * 
 */
void Country::print_info() {
    cout << name << ":" << endl;
    cout << "\t" << "Population: " << population << endl;
    cout << "\t" << "Infected: " << infected << endl;
    cout << "\t" << "Infection Rate: " << "(" << infectRate << " / 1000) people per day" << endl;
    cout << "\t" << "Chance of Spreading: " << spreadRate << endl;
}

/**
 * @brief getter for population
 * 
 * @return int population
 */
int Country::get_population() const{
    return population;
}

/**
 * @brief getter for number of infected
 * 
 * @return int number of infected
 */
int Country::get_infected() const{
    return infected;
}

/**
 * @brief getter for infect  rate
 * 
 * @return int infect rate
 */
int Country::get_infect_rate() const{
    return infectRate;
}

/**
 * @brief getter for spread rate
 * 
 * @return int spread rate
 */
int Country::get_spread_rate() const{
    return spreadRate;
}

/**
 * @brief updates the infect rate of a country
 */
void Country::update_infectRate() {
    if(infectRate < 1000) {
        infectRate = infectRate + ((double)infected / population) * 1000; // grows the larger the number of infected people get
        if(rand_int(1, 3) == 2) { // gets the game started and keeps the game moving at a reasonable rate
            infectRate++;
        }
        if(infectRate >= 1000) { // if infectRate maximizes
            infectRate = 1000; // set upper bound
            overtaken = true; // becomes overtaken
        }
    } else { // catches edge cases where overtaken countries don't become overtaken
        overtaken = true;
    }
}

/**
 * @brief updates the spread rate based on the infect rate
 * 
 */
void Country::update_spreadRate() {
    spreadRate = infectRate / 100;
}

/**
 * @brief takes info based on a country and randomly decides to add another country to infected countries
 * 
 * @param untouched list of all untouched countries
 * @param infected list of all countries that are infected
 * @param lastID ID of last infected country to sort and print in the same order
 */
void Country::spread(list<Country>& untouched, list<Country>& infected, int& lastID) {
    if(rand_int(0, 1001) <= spreadRate) { // generates random int 0-1000 and comapres to spreadrate 0-10
        if(untouched.size() == 0) { // edge case where final infected country might try to spread to nowhere
            return;
        } else {
            Country infectedCountry = get(untouched, rand_int(0, untouched.size())); // get a new country to infect
            infectedCountry.infect(); // infect the country
            infectedCountry.id = ++lastID; // assign and update lastID
            infected.push_back(infectedCountry); // push to infectedList
            untouched.remove(infectedCountry); // remove from untouched list
        }
    }
}

/**
 * @brief update the number of infected people
 * 
 * @param totalInfected number of total people infected in country
 */
void Country::infect(long long int& totalInfected) {
    for(int i = 0; i < infected; i ++) { // for each infected person
        int ODDS = rand_int(0, 1001); // random odds between 0-1000
        if((ODDS <= infectRate) && (infected < population)) {
            infected++; // continue updating infected of country and totalInfected
            totalInfected++;
        }
    }
}

/**
 * @brief seed an infected person into a country
 * 
 */
void Country::infect() {
    if(infected == 0) {
        infected++;
    }
}

/**
 * @brief Get a country from a list of countries
 * 
 * @param list1 get a list of countries
 * @param INDEX index of country to get
 * @return Country from list
 */
Country Country::get(list<Country> list1, const int INDEX) {
    typename list<Country>::iterator it;
    it = list1.begin();
    advance(it, INDEX);
    return *it;
}

#endif
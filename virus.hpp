#ifndef VIRUS_H
#define VIRUS_H

#include <math.h>
#include "country.hpp"
#include "simulation.hpp"

void infect(const int infectRate, int& infected, int&totalInfected) {
    for(int i = 0; i < infected; i ++) { // for each infected person
        int ODDS = rand_int(0, 1001);
        if(ODDS < infectRate) {
            infected++;
            totalInfected++;
        }
    }
}

void update_infectRate(const int POPULATION, const int INFECTED, int& infectRate) {
    //const int CONT_FACTOR = ceil(double(1/1000) / (1 / POPULATION)) ; // helps smooth scaling between different populations
    //infectRate = (double(INFECTED) / POPULATION) * CONT_FACTOR;
    infectRate = ceil((INFECTED / POPULATION) * 1000);
}

void update_spreadRate(const int infectRate, int& spreadRate) {
    spreadRate = infectRate / 100;
}

void spread(list<Country>& untouched, list<Country>& infected, const int spreadRate) {
    if(rand_int(0, 1001) < spreadRate) {
        spreadToCountry(infected, untouched);
    }
}

#endif
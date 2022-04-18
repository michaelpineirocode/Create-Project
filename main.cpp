/* CSCI 261 Final: Contagious Disease Simulator

 * Author: Michael Pineiro
 *
 * References:
 * 
 * Description: 
 */

#include <iostream>
#include <fstream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <string>
#include "country.hpp"
#include "virus.hpp"
#include "simulation.hpp"

using namespace std;

int main() {
    srand(time(0));
    ifstream csv;
    open_file(csv, "Data/population2020");
    list<string> countryNames= read_from_csv(csv, 1);
    for(int i = 0; i < countryNames.size(); i++) {
        cout << get(countryNames, i) << endl;
    }
}
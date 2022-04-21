/* CSCI 261 Final: Contagious Disease Simulator

 * Author: Michael Pineiro
 *
 * References:
 * Create a operator== for a class
 * https://stackoverflow.com/questions/37436468/invalid-operands-to-binary-expression-radiodevice-and-const-radiodevice
 * Use default destructor
 * https://stackoverflow.com/questions/13576055/how-is-default-different-from-for-default-constructor-and-destructor
 * 
 * Description: 
 */

#include <iostream>
#include <fstream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <string>
#include "HPP/country.hpp"
#include "HPP/simulation.hpp"

using namespace std;

int main() {
    srand(time(0));
    ifstream csv;
    open_file(csv, "Data/population.csv");
    list<string> countryNames= read_from_csv(csv, 1);
    list<string> populations = read_from_csv(csv, 2);
}
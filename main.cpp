/* CSCI 261 Final: Contagious Disease Simulator

 * Author: Michael Pineiro
 *
 * References:
 * Create a operator== for a class
 * https://stackoverflow.com/questions/37436468/invalid-operands-to-binary-expression-radiodevice-and-const-radiodevice
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
    open_file(csv, "Data/population2020");
    list<string> countryNames= read_from_csv(csv, 1);
    for(int i = 0; i < countryNames.size(); i++) {
        cout << get(countryNames, i) << endl;
    }
}
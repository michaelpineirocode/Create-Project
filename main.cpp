/* CSCI 261 Final: Contagious Disease Simulator

 * Author: Michael Pineiro
 *
 * References:
 * Create a operator== for a class
 * https://stackoverflow.com/questions/37436468/invalid-operands-to-binary-expression-radiodevice-and-const-radiodevice
 * Use default destructor
 * https://stackoverflow.com/questions/13576055/how-is-default-different-from-for-default-constructor-and-destructor
 * How to wait for enter
 * https://stackoverflow.com/questions/21257544/c-wait-for-user-input
 * How to define OS
 * https://stackoverflow.com/questions/5919996/how-to-detect-reliably-mac-os-x-ios-linux-windows-in-c-preprocessor
 * How to access cmd or terminal
 * https://stackoverflow.com/questions/14532496/try-to-execute-command-line-codes-from-c-linux
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
#include "HPP/functions.hpp"
#include "HPP/simulation.hpp"

using namespace std;

int main() {
    srand(time(0));
    
    ifstream csv;
    open_file(csv, "Data/population.csv");
    list<string> countryNames= read_ifstream_to_list(csv, 1, ',', true);
    csv.close();
    
    open_file(csv, "Data/population.csv");
    list<string> populationRaw = read_ifstream_to_list(csv, 2, ',', true);
    csv.close();
    list<int> population = string_to_int(populationRaw);
    populationRaw.clear(); // clear old list as it won't be used anymore
    if(menu_screen() == -1) {
        clear_screen();
        cout << "Goodbye!";
        return 1;
    } else {
        Simulate(countryNames, population);
    }
    cout << "Goodbye!" << endl;

}
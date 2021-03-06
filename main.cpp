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
 * Description: In this program I create a simulator which simulates the spread of a contagious disease
 * which spreads from country-to-country. The goal is to output the number of days it takes for a uncontrolled
 * contagious disease to infect every person. The program reads in data from Data/population.csv about country
 * population and creates lists of objects every country. The program also utilizes different .txt files from
 * within the /Data directory to display menu options. At the start a random country is chosen as "ground zero."
 * The user has the choice to press or hold enter to pass days, or to type in the command "skip" or "quit."
 * Skipping will run the simulation and print out the number of days that it took for the entire world to be
 * infected.
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
    srand(time(0)); // seed the random generator with current time
    
    ifstream csv; // read in the country name info info
    if(!open_file(csv, "Data/population.csv")) { // test to make sure file can be read
        cout << "Error reading file!" << endl;
        cout << "Goodbye!" << endl;
        return -1;
    };
    list<string> countryNames= read_ifstream_to_list(csv, 1, ',', true); // store country names in list
    csv.close();
    
    open_file(csv, "Data/population.csv"); // read info again
    list<string> populationRaw = read_ifstream_to_list(csv, 2, ',', true); // store string population data in list
    csv.close();
    list<int> population = string_to_int(populationRaw); // convert string list to integer list
    populationRaw.clear(); // clear old list as it won't be used anymore
    if(menu_screen() == -1) {
        clear_screen();
        cout << "Goodbye!";
        return 1;
    } else {
        Simulate(countryNames, population); // perform the simulation!
    }
    cout << "Goodbye!" << endl;

}
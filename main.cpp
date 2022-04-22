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

int menu_screen() {
    ifstream menuScreenInfo;
    open_file(menuScreenInfo, "Data/menuscreeninfo.txt");
    print(read_ifstream_to_list(menuScreenInfo, 1, ','));
    const int menuOption = get_user_input(1, 3);
    switch(menuOption) {
        case 1: {
            return 1;
        }
        case 2: {
            ifstream menuScreenInfo;
            open_file(menuScreenInfo, "Data/credits.txt");
            print(read_ifstream_to_list(menuScreenInfo, 1, ','));
            char waitForUser[] = "";
            cin >> waitForUser;            
            menu_screen();
            return -1;
        }
        case 3: {
            return -1;
        }
    }
}

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
        cout << "Goodbye!";
        return 1;
    }
    

}
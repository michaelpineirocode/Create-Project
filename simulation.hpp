#ifndef SIM_H
#define SIM_H

#include <cstdlib>
#include <fstream>
#include <list>
#include "country.hpp"

using namespace std;

bool open_file(ifstream &ifile, const string FILENAME) {
    ifile.open(FILENAME); // opens the file
    if(ifile.fail()) { // checks if it failed
        return false;
    } else {
        return true;
    }
}

list<string> read_from_csv(ifstream &ifile, const int columnNum) {
    char c;
    string currentWord = "";
    list<string> words;
    int commas = 0;
    
    while(ifile.get(c)) { // iterate through every character in the file
        if(isspace(c) == 0) { // if c is not whitespace
            currentWord.append(1, c); // add to the current word
        } else if((isspace(currentWord[0]) == 0) && currentWord != "") { // if it is whitespace and the string is not a whitespace char thusfar or empty
            words.push_back(currentWord); // send a new word
            currentWord = "";
        }
    }
    if(currentWord != ",") { // if it is whitespace and the string is not solely whitespace thusfar
        commas++;
        if(commas == columnNum) {
            words.push_back(currentWord); // send a new word
        }
    }
    return words;
}

int rand_int(const int MIN, const int MAX) {
    int num = (rand() % MAX) + MIN;
    return num;
}

Country get(list<Country> list1, const int INDEX) {
    typename list<Country>::iterator it;
    it = list1.begin();
    advance(it, INDEX);
    return *it;
}

void spreadToCountry(list<Country>& infected, list<Country>& untouched) {
    if(untouched.size() == 0) {
        return;
    } else {
        const Country infectedCountry = get(untouched, rand_int(0, untouched.size() - 1));
        infected.push_back(infectedCountry);
        untouched.remove(infectedCountry);
    }
}

#endif
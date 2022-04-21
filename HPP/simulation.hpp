#ifndef SIMULATION_H
#define SIMULATION_H

#include <cstdlib>
#include <fstream>
#include <list>

using namespace std;

bool open_file(ifstream &ifile, const string FILENAME) {
    ifile.open(FILENAME); // opens the file
    if(ifile.fail()) { // checks if it failed
        return false;
    } else {
        return true;
    }
}

list<string> read_from_csv(ifstream &ifile, const int columnNum){
    string currentLine;
    string currentWord = "";
    list<string> words;
    int commas = 0;
    
    while(getline(ifile, currentLine)) { // iterate through every character in the file
        //cout <<  currentLine << endl;
        commas = 0;
        currentWord = "";
        for(int i = 0; i < currentLine.size(); i++) {
            char c = currentLine.at(i);
            //cout << c;
            //cout << c << endl;
            if(c == ',') { // if it is whitespace and the string is not solely whitespace thusfar
                commas++;
                if(commas == columnNum) {
                    words.push_back(currentWord); // send a new word
                    break;
                } else {
                    currentWord = "";
                }
            } else {
                //cout << c;// << "!";
                currentWord.append(1, c);
            }
        }
    }
    return words;
}

int rand_int(const int MIN, const int MAX) {
    int num = (rand() % MAX) + MIN;
    return num;
}

template <typename T>
T get(list<T> list1, const int INDEX) {
    typename list<T>::iterator it;
    it = list1.begin();
    advance(it, INDEX);
    return *it;
}

#endif
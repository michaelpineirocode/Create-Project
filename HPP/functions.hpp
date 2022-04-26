#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cstdlib>
#include <fstream>
#include <list>

using namespace std;

/**
  * @brief Gets user input between two bounds
  * 
  * @param MIN the minimum bound
  * @param MAX  the maximum bound
  * @return int the choice of the user
  */
int get_user_input(const int MIN, const int MAX) {
    int option;
    bool correctOption = false;
    while(!correctOption) {
        // if the option is not an integer, continues to try to get input
        while(!(cin >> option)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter an option"<< endl;
        }
        // ensures that the integer is between the bounds
        if ((option >= MIN) && (option <= MAX)) {
            correctOption = true;
        } else {
            cout << "Please enter an option" << endl;
        }
    }
    return option;
}

void wait_for_enter(bool doTwice=true) {
    cin.get();
    if(doTwice) {
        cin.get();
    }
}

void clear_screen() {
#if defined(WIN32) || defined(_WIN32) || defined (__WIN32__) || defined(__NT__) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

bool open_file(ifstream &ifile, const string FILENAME) {
    ifile.open(FILENAME); // opens the file
    if(ifile.fail()) { // checks if it failed
        return false;
    } else {
        return true;
    }
}

list<string> read_ifstream_to_list(ifstream &ifile, const int columnNum, const char DELIM, bool skipFirstLine = false){
    string currentLine;
    string currentWord = "";
    list<string> words;
    int commas = 0;
    if(skipFirstLine) {
        getline(ifile, currentWord); // need to iterate through once to avoid headers
    }
    while(getline(ifile, currentLine)) { // iterate through every character in the file
        //cout <<  currentLine << endl;
        commas = 0;
        currentWord = "";
        for(int i = 0; i < currentLine.size(); i++) {
            char c = currentLine.at(i);
            //cout << c;
            //cout << c << endl;
            if(c == DELIM) { // if it is whitespace and the string is not solely whitespace thusfar
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
    int num = (rand() % MAX) + MIN - 1;
    return num;
}

template <typename T>
T get(list<T> list1, const int INDEX) {
    typename list<T>::iterator it;
    it = list1.begin();
    advance(it, INDEX);
    return *it;
}

template <typename T>
typename list<T>::iterator iterate(const int INDEX,  list<T> list1) {
    typename list<T>::iterator it;
    it = list1.begin();
    advance(it, INDEX);
    return it;
}

list<int> string_to_int(const list<string> OTHER) {
    list<int> current;
    for(int i = 0; i < OTHER.size(); i++) {
        current.push_back(stoi(get(OTHER, i)));
    }
    return current;
}

template <typename T>
void print(const list<T> OTHER) {
    for(int i = 0; i < OTHER.size(); i++) {
        cout << get(OTHER, i) << endl;
    }
}

#endif
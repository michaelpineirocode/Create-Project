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

int wait_for_enter(bool doTwice=true) {
    string command;
    getline(cin, command);
    if(command == "skip") {
        return 1;
    } else if (command == "quit") {
        return -1;
    } else if(doTwice) {
        cin.get();
        return 0;
    }
    return 0;
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

template <typename T>
list<T> remove(list<T> list1, const int INDEX) {
    list<T> list2;
    for(int i = 0; i < INDEX - 1; i++) {
        list2.push_back(get(list1, i));
    }
    for(int i = INDEX + 1; i < list1.size(); i++) {
        list2.push_back(get(list1, i));
    }
    return list2;
}

template <typename T>
list<T> merge(list<T> list1, list<T> list2) {
    
    list<T> list3;
    while((list1.size() > 0) && (list2.size() > 0)) { // while elements in both lists
        if(get(list1, 0).id > get(list2, 0).id) { // check if list 1 is greater
            list3.push_back(get(list2, 0)); // add to list 3
            list2 = remove(list2, 0); // remove the element
        }
        else {
            list3.push_back(get(list1, 0));
            list1 = remove(list1, 0);
        }
    }
    // one of the lists are empty now!
    while(list1.size() > 0) {
        list3.push_back(get(list1, 0));
        list1 = remove(list1, 0);
    }

    while(list2.size() > 0) {
        list3.push_back(get(list2, 0));
        list2 = remove(list2, 0);
    }

    return list3;
}

template <typename T>
list<T> mergeSort(list<T> list1) {
    // base case
    if(list1.size() <= 1) { 
        return list1;
    }

    // divide and split
    const int middle = (list1.size() / 2) - 1; // will round down
    
    
    list<T> left; // create a lefthand list
    for(int i = 0; i <= middle; i++) {
        left.push_back(get(list1, i));
       // cout << get(list1, i) << endl;
    }

    list<T> right; // create a righthand list
    for(int i = middle + 1; i < list1.size(); i++) {
        right.push_back(get(list1, i));
    }

    left = mergeSort(left);
    right = mergeSort(right);

    // ready to sort!
    return merge(left, right);
}

void print_file_to_screen(const string PATH) {
    clear_screen();
    ifstream menuScreenInfo;
    open_file(menuScreenInfo, PATH);
    print(read_ifstream_to_list(menuScreenInfo, 1, ','));
    wait_for_enter();
}

#endif
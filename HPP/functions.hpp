#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cstdlib>
#include <fstream>
#include <list>
#include <limits>

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
            cout << "Please enter an option between " << MIN << " and " << MAX << endl;
        }
        // ensures that the integer is between the bounds
        if ((option >= MIN) && (option <= MAX)) {
            correctOption = true;
        } else {            
            cout << "Please enter an option between " << MIN << " and " << MAX << endl; 
        }
    }
    return option;
}

/**
 * @brief Converts a string to lowercase
 * 
 * @param OTHER the other string
 * @return string that is completely lowercase
 */
string convert_to_lowercase(const string OTHER) {
    string newWord = ""; 
    for(int i = 0; i < OTHER.size(); i++) {
        char c = OTHER.at(i);
        newWord.append(1, ::tolower(c)); // append lowercase version of letter to newWord
    }
    return newWord;
}

/**
 * @brief waits for the user to press enter or enter a command
 * 
 * @param doTwice whether to wait for user to press enter twice
 * @return int corresponding whether the user entered a command or skipped
 */
int wait_for_enter(bool doTwice=true) {
    string command; // what the user types
    getline(cin, command);
    command = convert_to_lowercase(command); // convert to lowercase so case doesn't matter
    if(command == "skip") { 
        return 1;
    } else if (command == "quit") {
        return -1;
    } else if(doTwice) { // sometimes required to press enter twice
        cin.get(); // get a line again
        return 0;
    } // if none of these are true, continue the program
    return 0;
}

/**
 * @brief tests what OS user is on and then clears the screen accordingly
 * 
 */
void clear_screen() {
#if defined(WIN32) || defined(_WIN32) || defined (__WIN32__) || defined(__NT__) || defined(_WIN64) // test if windows
    system("cls");
#else
    system("clear"); // if linux or OSX then use clear
#endif
}

/**
 * @brief opens a filestream
 * 
 * @param ifile the file stream for opening
 * @param FILENAME the name of the file
 * @return true if the file opened properly
 * @return false if the file did not open properly
 */
bool open_file(ifstream &ifile, const string FILENAME) {
    ifile.open(FILENAME); // opens the file
    if(ifile.fail()) { // checks if it failed
        return false; // IT FAILED
    } else {
        return true;
    }
}

/**
 * @brief reads file and stores a certain column as list based on deliniator
 * 
 * @param ifile input file stream
 * @param COLUMN_NUM the column that needs to be read in
 * @param DELIM the deliminator between columns
 * @param skipFirstLine whether to skip a header
 * @return list<string> of all contents in the file
 */
list<string> read_ifstream_to_list(ifstream &ifile, const int COLUMN_NUM, const char DELIM, bool skipFirstLine = false){
    string currentLine;
    string currentWord = "";
    list<string> words;
    int commas = 0; // commas are often used as the deliminator, so this is the number of deliminators found
    if(skipFirstLine) {
        getline(ifile, currentWord); // need to iterate through once to avoid headers
    }
    while(getline(ifile, currentLine)) { // iterate through every line in the file
        commas = 0; // reset number of deliniators
        currentWord = "";
        for(int i = 0; i < currentLine.size(); i++) {
            char c = currentLine.at(i); // get every character
            if(c == DELIM) { // keep track of number of deliminators we've found
                commas++; 
                if(commas == COLUMN_NUM) {
                    words.push_back(currentWord); // add a new word
                    break; // go to the next line
                } else {
                    currentWord = ""; // reset the info of the column so far
                }
            } else {
                currentWord.append(1, c); // if it's not a deliminator, add the character to the current word
            }
        }
    }
    return words;
}

/**
 * @brief Returns a random integer within bounds
 * 
 * @param MIN inclusive min
 * @param MAX exclusive max
 * @return int the random number
 */
int rand_int(const int MIN, const int MAX) {
    int num = (rand() % MAX) + MIN; // get a random number between [MIN, MAX)
    return num;
}

/**
 * @brief iterates through a list and gets the element at given index
 * 
 * @tparam T template variable
 * @param list1 the list to iterate through
 * @param INDEX the index of the element to get
 * @return T the element at the INDEX position
 */
template <typename T>
T get(list<T> list1, const int INDEX) {
    typename list<T>::iterator it; // create an iterator
    it = list1.begin(); // assign to start of list
    advance(it, INDEX); // go through each item until index
    return *it; // return value of list at point of iterator
}

/**
 * @brief converts a list of strings to a list of integers
 * 
 * @param OTHER list of strings
 * @return list<int> list of integers
 */
list<int> string_to_int(const list<string> OTHER) {
    list<int> current;
    for(int i = 0; i < OTHER.size(); i++) {
        current.push_back(stoi(get(OTHER, i))); // use stoi() function to push string to list of integers 
    }
    return current;
}

/**
 * @brief print a list
 * 
 * @tparam T remplate variable
 * @param OTHER the list to print
 */
template <typename T>
void print(const list<T> OTHER) {
    for(int i = 0; i < OTHER.size(); i++) { // every element in the list
        cout << get(OTHER, i) << endl; // get the item and print the value
    }
}

/**
 * @brief Used to remove an element from a list
 * 
 * @tparam T the template variable
 * @param list1 the list to remove an element from
 * @param INDEX the position of the element to remove
 * @return list<T> a list with the element removed
 */
template <typename T>
list<T> remove(list<T> list1, const int INDEX) {
    list<T> list2; 
    for(int i = 0; i < INDEX - 1; i++) {
        list2.push_back(get(list1, i)); // add to list up UNTIL the removal index
    }
    for(int i = INDEX + 1; i < list1.size(); i++) {
        list2.push_back(get(list1, i)); // add all elements AFTER the indexed element
    }
    return list2; // return new list
}

/**
 * @brief merge two lists together
 * 
 * @tparam T template variable
 * @param list1 the first list
 * @param list2 the second list
 * @return list<T> the merged list
 */
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

/**
 * @brief sort a list
 * 
 * @tparam T template variable
 * @param list1 the list to sort
 * @return list<T> a sorted list
 */
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

/**
 * @brief prints a file to the screen
 * 
 * @param PATH the path to the file
 */
void print_file_to_screen(const string PATH) {
    clear_screen();
    ifstream menuScreenInfo;
    if(!open_file(menuScreenInfo, PATH)) {
        return; // if the file can't be opened, do nothing.
    }
    print(read_ifstream_to_list(menuScreenInfo, 1, ','));
    menuScreenInfo.close();
    wait_for_enter();
}

#endif
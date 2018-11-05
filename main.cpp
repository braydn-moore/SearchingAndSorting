#include <iostream>
#include <algorithm>
#include <fstream>
#include <boost/regex.hpp>
#include <chrono>
#include <random>
#include "boost/filesystem.hpp"
#include "mergeSort.h"
#include "countSort.h"
#include "selectionSort.h"
#include "insertionSort.h"
#include "bubbleSort.h"
#include "quickSort.h"
#include "timSort.h"
#include "binarySearch.h"
#include "intelligentInput.h"

/******************************
 * Program: Searching and sorting program
 * Author: Braydn Moore
 * Due Date: I have no clue
 * Description: A program which can generate unsorted data, read it, sort it, search it, and write the sorted data
 ******************************/

/*
 * DIFFERENCES BETWEEN JAVA AND C++:
 *  1. Operator Overloading: C++ allows you to overload operators of data typed which allows you to run custom code when
 *                           doing for example: obj1+obj2 instead of java in which you would need obj1.add(obj2)
 *
 *  2. Preprocessor Directives: C++ allows you to use preprocessor directives which are replaced at compile time with
 *                              the expanded code
 *
 *  3. Pointers: C++ allows you to have pointers which point to addresses in memory as opposed to the actual value where
 *                  as Java handles memory management for you
 *
 *  4. Structs: C++ allows for the creation of structs which are data types that allow you to store information. Java
 *                  only has classes. However it is worth noting the only difference between classes and structs is the
 *                  default visibility of the member items. Classes default functions to private whereas structs default
 *                  to public
 *
 *  5. Headers: Java classes are all contained in .java files. C++ has headers which allows for both the declaring and
 *              definition of functions. Cpp files will define the declared functions in the headers if needed
 */

// print debug messages?
#define DEBUG 0

#ifdef __MINGW32__
#define OS "win"
#else
#define OS "linux"
#endif

// macro to quickly create a sortingFunction struct using the value passed and the literal value passed as a string
#define FUNCTION(name) {name, #name}

// define sorting function as a pointer to one of the sorting functions
template<typename T>
using sortFunction = T(*)(T &);

// create a struct to store the function pointer to a sorting function as well as the name
template<typename T>
struct sortingFunction {
    sortFunction<T> func;
    std::string name;

    // override the function calling parameter to call the function pointer in the struct
    T operator()(T &vector) {
        return (*this->func)(vector);
    }

};

// array of sorting functions
template<typename T>
struct sortingFunction<T> sortingFunctions[] = {
        FUNCTION(&bubbleSort),
        FUNCTION(&countSort),
        FUNCTION(&insertionSort),
        FUNCTION(&mergeSort),
        FUNCTION(&quickSort),
        FUNCTION(&selectionSort),
        FUNCTION(&timSort)
};

// replace all occurences in a string with something else
std::string replace(std::string &str, const std::string &toReplace, const std::string &toAdd) {
    // start position of to replace
    size_t start_pos = 0;
    // while toReplace exists in the string replace it and increment the start position so we find the next one
    while ((start_pos = str.find(toReplace, start_pos))!=std::string::npos) {
        str.replace(start_pos, toReplace.length(), toAdd);
        start_pos+=toAdd.size();
    }
    return str;
}

// operator overloader to print a sortingFunction struct
template<typename T>
std::ostream &operator<<(std::ostream &os, sortingFunction<T> &function) {
    // if the function name has not been processed then process it
    if (function.name.size() && function.name[0] == '&') {
        // get rid of the & at the front that comes as a result of having to pass the functions as &functionName to the macro
        function.name.erase(0, 1);
        // capitalize the string
        function.name[0] = (char) std::toupper(function.name[0]);
        // add a space between sort and the name
        replace(function.name, "Sort", " Sort");
    }
    // print the name
    return os << function.name;
}

// operator overloading for printing a vector
template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vector) {
    // print the opening bracket
    os << "[";
    // for each value in the vector
    for (int i = 0; i < vector.size(); i++)
        os << vector[i]<<(i<vector.size()-1?", ":"");
    // print the closing bracket and a newline
    os << "]"<<std::endl;
    return os;
}

// operator overloading to write a vector to a file
template<typename T>
std::fstream& operator<<(std::fstream &input, std::vector<T> &vector) {
    // for every value in the vector write the value and then a space
    for (T value : vector)
        input << value << " ";
    return input;
}

// remove whitespace at the end of a string
std::string endingTrim(std::string &input) {
    // erase all whitespace at the end
    input.erase(input.find_last_not_of(" \t\n\r\f\v") + 1);
    return input;
}

// split a string along a delimiter
std::vector<std::string> split(const std::string &input, const std::string &search) {
    std::vector<std::string> toReturn;

    // position of last found match of delimiter
    size_t last = 0;
    // index of the next found delimiter after last
    size_t next = 0;
    // while a delimiter still exists in the string split the string
    while ((next = input.find(search, last)) != std::string::npos) {
        toReturn.emplace_back(input.substr(last, next - last));
        last = next + 1;
    }
    // add the remaining piece of the string
    toReturn.emplace_back(input.substr(last));
    // return the vector
    return toReturn;
}

// cleanup the input from a file
std::string cleanUpInput(std::string &input) {
    // replace all 2+ spaces with and a newline if it is there with just one space
    input = boost::regex_replace(input, boost::regex(R"(\s\s+(\n?))"), " ");
    return input;
}

// sort function
std::vector<int> sort(std::vector<int> numbers, std::fstream& file){
    // print out all the sorting functions
    int counter = 1;
    for (sortingFunction<std::vector<int>> function : sortingFunctions<std::vector<int>>)
        std::cout << (counter++) << ". " << function << std::endl;

    // get the users sorting technique choice
    std::cout << "Enter the sorting technique to use:";
    int choice;
    std::cin >> choice;
    // get the current time
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    // sort the vector
    numbers = sortingFunctions<decltype(numbers)>[choice - 1](numbers);
    // get the time after the sort
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    // print the number of milliseconds it took to complete the sort
    std::cout<<"It took "<<std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()<<" milliseconds to sort the vector"<<std::endl;
    // print whether or not the vector is sorted properly if we are debugging
    if (DEBUG)
        std::cout<<(std::is_sorted(numbers.begin(), numbers.end())?"Array is sorted":"Array is not sorted")<<std::endl;

    // write the vector to the file overwriting the unsorted version
    file << numbers;
    // close the file
    file.close();
    // return the vector if we are storing it somewhere after
    return numbers;
}

// search for a value in the file
void search(std::vector<int> numbers, std::fstream& file){
    // get the value to search for
    std::string search;
    std::cout<<"Enter the value to search for: ";
    std::getline(std::cin, search);

    /*
     * if the arrays is not sorted then binary search will not work so ask the user if they want to sort the array
    and continue or just leave
     */
    if (!std::is_sorted(numbers.begin(), numbers.end())){
        std::cout<<"Error the array must be sorted to search, would you like to sort it(y/n)?:";
        char answer;
        std::cin>>answer;
        if (answer == 'y') numbers = sort(numbers, file);
        else { file.close();exit(0);}
    }
    // get the index of the value we are searching for
    int index = binarySearch(numbers, std::stoi(search));

    // print a message if the value was not found or if it was found and the index it was found at
    std::cout<<search<<(index==-1?" was not found":" was found at index "+std::to_string(index))<<std::endl;
    file.close();
}

void generate(std::fstream& file){
    // get the information for the data set to generate
    std::cout<<"Enter the lower bound: ";
    int lowBound, highBound, size;
    std::cin>>lowBound;
    std::cout<<"Enter the high bound: ";
    std::cin>>highBound;
    std::cout<<"Enter the size of the dataset:";
    std::cin>>size;

    // use the current time since epoch as the seed for the randomization
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    // create the randomization engine using the seed
    std::default_random_engine dre(seed);
    // create a uniform distribution of random numbers between the high and the low using the engine
    std::uniform_int_distribution<int> di(lowBound,highBound);

    // create the vector of the given data set size
    std::vector<int> vector(size);

    // fill the vector with random numbers
    std::generate(vector.begin(), vector.end(), [&]{ return di(dre);});
    // write the vector to a file
    file<<vector;
    // close the file
    file.close();
}

// return a vector of strings containing all the files in the current directory to read from
std::vector<std::string> getFiles() {
    std::vector<std::string> files;
    boost::filesystem::directory_iterator end;

    // for every file in the current directory
    for (boost::filesystem::directory_iterator file(boost::filesystem::path(".")); file != end; ++file) {
        // if it is a regular file then remove the leading "./" in the file name and append it to the vector
        if (is_regular_file(file->path())) {
            // not this has to be stored in a string as the value is a const which does not work for the replace function
            std::string name = file->path().string();
            // replace either "./" or ".\" as windows and linux use different slashes
            files.emplace_back(OS=="win"?replace(name, ".\\", ""):replace(name, "./", ""));
        }
    }

    if (DEBUG)
        std::cout<<"Files are: "<<files<<std::endl;
    return files;
}

int main() {
    // get the operation for the current session using intelligent input which allows for misspellings
    std::cout<<"Would you like to search or sort or generate?: ";
    std::string choice = getIntelligentInput(3, DEBUG, "search", "sort", "generate");
    // if the user did not choose a valid choice then exit
    if (choice != "search" && choice!="sort" && choice!="generate"){
        std::cout<<"That's not an option"<<std::endl;
        return -1;
    }
    // create the file object
    std::fstream file;
    std::string fileName;
    // get the object filename
    std::cout << "Enter the file to "<<choice<<": ";
    /* if the user is opening a file use intelligent input to guess but if they are generating we don't want to correct
    * there file name choice
    */
    if (choice!="generate")
        fileName = getIntelligentInput(4, DEBUG, getFiles());
    else
        std::getline(std::cin, fileName);

    // open the file
    file.open(fileName, std::fstream::out | std::fstream::in);

    // if we are not generating a new file and the file doesn't exist then exit because there's nothing to search/sort
    if (!file && choice!="generate") {
        std::cout << "File not found" << std::endl;
        return -1;
    }
    // otherwise if we are generating a new file generate it and leave
    else if (choice == "generate"){
        generate(file);
        return 0;
    }

    // read the file contents into a string
    std::string fileContents((std::istreambuf_iterator<char>(file)),
                             (std::istreambuf_iterator<char>()));
    // clear file eof flag from reading to the end of the file
    file.clear();
    // return to the beginning of the file to write
    file.seekp(0, std::ios_base::beg);
    // get rid of the whitespace at the end of the string
    endingTrim(fileContents);
    // clean up the newlines double spaces etc and split on the spaces
    std::vector<std::string> strings = split(cleanUpInput(fileContents), " ");
    // convert the string vector to an int vector using a lambda
    std::vector<int> numbers;
    std::transform(strings.begin(), strings.end(), std::back_inserter(numbers),
                   [](const std::string &string) { return std::stoi(string); });

    // call the respective function based on the user's input
    if (choice == "search")
        search(numbers, file);
    else if (choice == "sort")
        sort(numbers, file);
}
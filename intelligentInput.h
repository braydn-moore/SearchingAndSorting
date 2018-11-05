//
// Created by x3vikan on 6/16/18.
//

#ifndef STAGE4_INTELLIGENTINPUT_H
#define STAGE4_INTELLIGENTINPUT_H

#include <string>
#include <vector>
#include <iostream>


// gets the minimum value between two values
template<typename T>
T vmin(T val1, T val2)
{
    return val1 < val2 ? val1 : val2;
}

//gets the minimum value of multiple values passed in using variadic inputs
template<typename T, typename... Ts>
T vmin(T val1, T val2, Ts&&... vs)
{
    // return the minimum value recursively
    return val1 < val2 ?
           vmin(val1, std::forward<Ts>(vs)...) :
           vmin(val2, std::forward<Ts>(vs)...);
}

// calculate the minimum distance(number of insertions, deletions, shifts, etc.) between two strings
int levinsteinsDistance(const std::string s1, const std::string s2){
    // get the sizes of the strings
    const size_t len1 = s1.size(), len2 = s2.size();
    // create a vector array for the distances, the value at [len1][len2] is the minimum distance
    std::vector<std::vector<unsigned int>> distances(len1+1, std::vector<unsigned int>(len2+1));

    // set the starting distance to 0
    distances[0][0] = 0;
    // set the first row and column to the corresponding column/row value
    for (unsigned int i = 1; i<=len1; i++) distances[i][0] = i;
    for (unsigned int i = 1; i<=len2; i++) distances[0][i] = i;

    // for every character in both strings
    // if the two items are equal the cost is zero otherwise the cost is 1
    // set the cell in the matrix to the minimum of:
                                                     // 1. The cell above plus one
                                                     // 2. The cell to the left plus one
                                                     // 3. The cell diagonally up and left plus the cost
    for (unsigned int i = 1; i<=len1; i++)
        for (unsigned int j = 1; j<=len2; j++)
            distances[i][j] = vmin(distances[i-1][j]+1, distances[i][j-1]+1, distances[i-1][j-1]+(s1[i-1]==s2[j-1]?0:1));

    // return the minimum distance
    return distances[len1][len2];
}

// convert a variadic value to a vector of strings
template <typename... Args>
std::vector<std::string> variadicToStringVector(Args... args) {
    // create the result vector
    std::vector<std::string> result;
    // convert the variadic argument into the vector of its type
    auto initList = {args...};
    using T = typename decltype(initList)::value_type;
    std::vector<T> expanded{initList};
    // set result to the size of the variadic vector
    result.resize(expanded.size());
    // transform the variadic vector into the string vector
    std::transform(expanded.begin(), expanded.end(), result.begin(), [](T value) { return std::string(value); });
    // return the string vector
    return result;
}

// get the best match of the checks and the input given the maximum distance
std::string bestMatch(std::string input, int maxDistance, std::vector<std::string> checks, bool debug) {
    // set the min distance and distance variables
    int minDistance = -1, distance;
    // best match to return
    std::string bestMatch;
    // for every item that could be a match
    for (const auto &value : checks) {
        // if the item and the check is the exact match then return that match
        if (value == input) return input;
        // otherwise get the distance between the two items and if it is less than the min distance then it is now the best match
        else if ((distance = levinsteinsDistance(input, value)) < minDistance || minDistance == -1) {
            minDistance = distance;
            bestMatch = value;
        }
    }
    if (debug)
        std::cout<<"The best match was "<<bestMatch<<" with a score of "<<minDistance<<std::endl;

    // if the min distance is less than the max accepted distance return the best match otherwise return nothing
    if (minDistance <= maxDistance)
        return bestMatch;
    else
        return "";
}

// intelligent input
std::string getIntelligentInput(int maxDistance, bool debug, std::vector<std::string> checks){
    // get the user input
    std::string input;
    std::getline(std::cin, input);
    // return the best match to the input
    return bestMatch(input, maxDistance, checks, debug);
}

// intelligent input
template <typename... T>
std::string getIntelligentInput(int maxDistance, bool debug, T... checks){
    // get the value of the intelligent input
    return getIntelligentInput(maxDistance, debug, variadicToStringVector(checks...));
}

#endif //STAGE4_INTELLIGENTINPUT_H

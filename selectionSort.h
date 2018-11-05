#ifndef STAGE4_SELECTIONSORT_H
#define STAGE4_SELECTIONSORT_H

/**********************************************************
 * Program	:  Selection Sort
 * Author	:  Braydn Moore
 * Due Date	:  End of Unit
 * Description	: A sorting technique which finds the next smallest value that hasn't been sorted and swaps it with the
 *                  value in the position it should be in. The best, average, and worst case time complexity is O(n^2)
 ***********************************************************/

#include <iostream>

// finds the index of the min value in the given vector
template <typename T>
int getMinIndex(T& vector, int start){
    int index = start;

    for (int counter = start; counter<vector.size(); counter++)
        if (vector[counter]<vector[index])
            index = counter;

    return index;
}

// the sort itself
template <typename T>
T selectionSort(T& vector){
    // for each item in the vector
    for (int counter = 0; counter<vector.size()-1; counter++)
        // find the next smallest number and swap the number at the current position with the next smallest number
        std::swap(vector[getMinIndex(vector, counter)], vector[counter]);
    return vector;
}

#endif //STAGE4_SELECTIONSORT_H

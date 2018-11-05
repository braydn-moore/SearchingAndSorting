#ifndef STAGE4_SORTS_H
#define STAGE4_SORTS_H

/**********************************************************
 * Program	:  Merge Sort
 * Author	:  Braydn Moore
 * Due Date	:  End of Unit
 * Description	: A sort that sorts while merging two portions of an array. The best, average, and worst time complexity
 *                  is O(n log n)
 ***********************************************************/

#include <iostream>
#include <vector>
#include <iterator>

// get the values in a subrange of the given vector as a vector
template <typename T>
T range(T vector, int start, int end){
    return T(vector.begin()+start, vector.begin()+end);
}

// merge two vectors
template <typename T>
T merge(T a, T b){
    // the final vector size will be the combined size of a and b
    T ret(a.size()+b.size());
    // i is the index for a and j is the index for b
    int i = 0, j = 0;
    // for each space in the return vector
    for (int counter = 0; counter<ret.size(); counter++){
        // if we are out of values in the a vector fill the remaining spaces with the b vector
        if (i>=a.size()) ret[counter] = b[j++];
        // otherwise if we are out of range in the b vector fill the remaining spaces with the a vector
        else if (j>=b.size()) ret[counter] = a[i++];
        // if the value at the current position of a is less than or equal to the value of the current position at b get the value from a
        else if (a[i]<=b[j]) ret[counter] = a[i++];
        // otherwise the value from b is less than that of a so use that
        else ret[counter] = b[j++];
    }

    return ret;
}

template <typename T>
T mergeSort(T& array){
    // if the array is of size 1 or 0 then it is already sorted
    if (array.size()<2)
        return array;

    // find the middle of the array
    int middle = array.size()/2;
    // get the left and the right side of the array
    T left = range(array, 0, middle);
    T right = range(array, middle, array.size());
    // merge the two merge sorted arrays after being called recursively
    return merge(mergeSort(left), mergeSort(right));
}

#endif //STAGE4_SORTS_H

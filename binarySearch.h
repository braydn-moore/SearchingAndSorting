#ifndef STAGE4_BINARYSEARCH_H
#define STAGE4_BINARYSEARCH_H

/**********************************************************
 * Program	:  Binary Search
 * Author	:  Braydn Moore
 * Due Date	:  End of Unit
 * Description	: A searching technique that requires a sorted array but has a worst case and average performance of
 *                  O(log n)
 ***********************************************************/

// binary search function using generics
template <typename T>
int binarySearch(T vector, typename T::value_type search){
    // initialize the variables
    int low = 0, high = vector.size(), middle;

    // while our high value is greater than or equal to low keep searching
    while (high>=low){
        // get the middle of the array
        middle = (high+low)/2;
        // check if it is the value we are searching for
        if (vector[middle] == search) return middle;
        // otherwise if the value we are looking for is greater than the middle value search the upper half of the current range
        else if (vector[middle]<search) low = middle+1;
        // otherwise the value must be less than the middle value so search the bottom half of the current of the current range
        else high = middle-1;
    }
    // if the value is not in the array return -1
    return -1;
}


#endif //STAGE4_BINARYSEARCH_H

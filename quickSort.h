#ifndef STAGE4_QUICKSORT_H
#define STAGE4_QUICKSORT_H

/**********************************************************
 * Program	:  Quick Sort
 * Author	:  Braydn Moore
 * Due Date	:  End of Unit
 * Description	: A sorting technique that uses a pivot to sort partitions of an array. The average and best
 *                  time complexity is O(n log N) and the worst is O(n^2)
 ***********************************************************/

#include <algorithm>

// partition a range in a vector
template <typename T>
int partition(T& vector, int left, int right){
    // set the left most value as the pivot
    auto pivot = vector[left];
    // set the position to set the pivot after the reorganization
    int newPivotPosition = left;

    // arrange all values in the range around the pivot eg. before or after the pivot if it is less or greater than
    for (int counter = left+1; counter<right; counter++)
        if (vector[counter]<pivot)
            std::swap(vector[counter], vector[++newPivotPosition]);

    // move the pivot to the position it should be in
    std::swap(vector[left], vector[newPivotPosition]);
    // return the position of the pivot
    return newPivotPosition;
}

// recursive quick sort for a vector in a range
template <typename T>
void quickSortRecursive(T &vector, int left, int right){
    // return if left is past right
    if (left>=right) return;

    // get the partition center
    int partitionValue = partition(vector, left, right);
    // sort the left and right side of the partition
    quickSortRecursive(vector, left, partitionValue);
    quickSortRecursive(vector, partitionValue + 1, right);
}

// main sort
template <typename T>
T quickSort(T& vector){
    // sort the vector's entire range
    quickSortRecursive(vector, 0, vector.size());
    // return the vector
    return vector;
}

#endif //STAGE4_QUICKSORT_H

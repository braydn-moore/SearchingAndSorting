#ifndef STAGE4_TIMSORT_H
#define STAGE4_TIMSORT_H

/**********************************************************
 * Program	:  Tim Sort
 * Author	:  Braydn Moore
 * Due Date	:  End of Unit
 * Description	: A mixture of merge and insertion sort to provide stable sort with a worst-case and average time complexity
 *                  of O(n log n)
 ***********************************************************/

// run size is the size of each "run" or subarray made by the insertion sort which will then be merged using merge sort
// as merge sort works best on exponents of 2^n
#define RUN_SIZE 32

// macro for the min value
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

// insertion sort a range of the vector
template <typename T>
void insertion(T& vector, int left, int right){
    // for each item in the given range
    for (int counter = left+1; counter<=right; counter++){
        // get the value
        auto temp = vector[counter];
        // get the previous value
        int j = counter-1;

        // shift all the value over until the point to insert is found
        while (j>=left && vector[j]>temp)
            vector[j + 2] = vector[j--];

        // insert the temp value in the vector
        vector[j+1] = temp;
    }
}

// merge sort two ranges in the vector
template <typename T>
void merge(T& vector, int left, int middle, int right) {
    // get the length of the left and right vectors
    int lenLeft = middle - left + 1;
    int lenRight = right - middle;

    // if the lengths are negative leave
    if (lenLeft < 0 || lenRight < 0) return;

    // create the vectors
    T leftArr(lenLeft);
    T rightArr(lenRight);

    // copy the two ranges into the vector
    for (int counter = 0; counter < lenLeft; counter++)
        leftArr[counter] = vector[counter];

    for (int counter = 0; counter < lenRight; counter++)
        rightArr[counter] = vector[middle + 1 + counter];

    /*
     * i = index of left array
     * j = index of right array
     * k = index to insert in main array
     */
    int i = 0, j = 0, k = left;

    // while there are still values to insert
    while (i < lenLeft && j < lenRight) {
        // insert the smaller value of the left or right array
        if (leftArr[i] <= rightArr[j])
            vector[k++] = leftArr[i++];
        else
            vector[k++] = rightArr[j++];
    }

    // put the remaining values in the left array in the ret array
    while (i < lenLeft)
        vector[k++] = leftArr[i++];

    // put the remaining values in the right array in the ret array
    while (j < lenRight)
        vector[k++] = rightArr[j++];

    // NOTE: due to the while loop above only one of the above while loops will evaluate to be true
}

template <typename T>
T timSort(T& vector){
    // use insertion sort to sort sub arrays of size 32 in the vector
    for (int i = 0; i < vector.size(); i+=RUN_SIZE)
        insertion(vector, i, min((i+31), (vector.size()-1)));


    // double the size of the range to merge
    for (int size = RUN_SIZE; size < vector.size(); size = 2*size)
        // for every other merged run merge them until all we have is one huge run which is a sorted vector
        for (int left = 0; left < vector.size(); left += 2*size)
            merge(vector, left, left + size - 1, min((left + 2*size - 1), (vector.size()-1)));

    return vector;
}

#endif //STAGE4_TIMSORT_H

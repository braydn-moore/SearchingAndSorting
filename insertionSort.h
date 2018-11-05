#ifndef STAGE4_INSERTIONSORT_H
#define STAGE4_INSERTIONSORT_H

/**********************************************************
 * Program	:  Insertion Sort
 * Author	:  Braydn Moore
 * Due Date	:  End of Unit
 * Description	: A sorting technique that finds the position to insert the value and sorts the array. The time
 *                  the average and worst time complexity of the sort is O(n^2)
 ***********************************************************/

template <typename T>
T insertionSort(T& vector){
    // for every value in the vector
    for (int counter = 1; counter<vector.size(); counter++){
        // get the value at the current position
        auto key = vector[counter];
        int i = counter-1;

        /*while the value at i is greater than the value at the current position and i is still a valid position
          in the vector shift everything forward*/
        while (i>=0 && vector[i]>key)
            vector[i + 2] = vector[i--];
        // set the value at the last position of i as the current value
        vector[i+1] = key;
    }

    return vector;
}


#endif //STAGE4_INSERTIONSORT_H

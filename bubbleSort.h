#ifndef STAGE4_BUBBLESORT_H
#define STAGE4_BUBBLESORT_H

/**********************************************************
 * Program	:  Bubble Sort
 * Author	:  Braydn Moore
 * Due Date	:  End of Unit
 * Description	: A sorting techniques that mimics the rising of bubbles and bubbles the largest item to the top.
 *                  This sort has an average and worst case time complexity of O(n^2)
 ***********************************************************/

#include <algorithm>

// bubble sort a vector
template <typename T>
T bubbleSort(T& vector){
    // for each index in the vector
    for (int i = 0; i<vector.size(); i++)
        // the last i indexes are already in place so we can skip them
        for (int j = 0; j<vector.size()-i-1; j++)
            // swap the given values if they are out of place
            if (vector[j]>vector[j+1])
                std::swap(vector[j], vector[j+1]);
    // return the vector
    return vector;
}

#endif //STAGE4_BUBBLESORT_H

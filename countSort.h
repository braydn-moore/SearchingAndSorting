#ifndef STAGE4_COUNTSORT_H
#define STAGE4_COUNTSORT_H

/**********************************************************
 * Program	:  Count Sort
 * Author	:  Braydn Moore
 * Due Date	:  End of Unit
 * Description	: A sorting technique that can only sort integer arrays. It uses the number of occurrences of distinct
 *                  integers. The time complexity of the average, best, and worst case is O(n+k)
 ***********************************************************/

#include <vector>

std::vector<int> countSort(std::vector<int>& sort){
    // make a vector of size sort
    std::vector<int> ret(sort.size());

    // assume the highest number that will be given is 10,000,000
    int count[1000*100*100];
    // zero the entire array
    memset(count, 0, (1000*100*100)*sizeof(*count));

    // for each value in the array increment the value at the value's index in the array
    for (int var : sort)
        count[var]++;

    // set count[i] so that count[i] contains the actual position of the value in the output array
    for (int i = 1; i<1000*100*100; i++)
        count[i]+=count[i-1];

    // build the output array
    for (int i = 0; i<sort.size(); i++)
        ret[--count[sort[i]]] = sort[i];

    return ret;
}

#endif //STAGE4_COUNTSORT_H

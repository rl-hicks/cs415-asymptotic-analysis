//
// Created by levi on 2/21/2026.
//

#include "SortingAlgorithms.h"



void SortingAlgorithms::swap(int Arr[],int bigIndex,int n) {
    int temp = Arr[bigIndex];
    Arr[bigIndex] = Arr[n];
    Arr[n] = temp;
}





void SortingAlgorithms::insertSort2(int Comparable[], int n, long long &numComp) { // Insertion Sort
    for (int i = 1; i < n; i++) // Insert i'th record
        for (int j = i; (j > 0) && (Comparable[j] < Comparable[j-1]); j--)
            swap(Comparable, j, j-1);
}

void SortingAlgorithms::insertSort(int Comparable[], int n, long long &comparison_count) {
    for (int i = 1; i < n; i++) {   // Insert i'th record

        for (int j = i; j > 0; j--) {

            comparison_count++;   // Count element comparison

            if (Comparable[j] < Comparable[j-1]) {
                swap(Comparable, j, j-1);
            } else {
                break;  // Stop if already in correct position
            }
        }
    }
}


void SortingAlgorithms::selectionSort(int Comparable[], int n, long long &comparison_count) {
    for (int i = 0; i < n-1; i++) {                     // Select i'th biggest record
        int bigindex = 0;                               // Current biggest index
        for (int j = 1; j < n-i; j++) {                 // Find the max value
            comparison_count++;
            if (Comparable[j] > Comparable[bigindex]) { // Found something bigger
                bigindex = j;                           // Remember bigger index
            }
        }
        swap(Comparable, bigindex, n-i-1);           // Put it into place
    }
}




//
// Created by levi on 2/21/2026.
//

#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H



class SortingAlgorithms {

public:
    void insertSort(int Comparable[], int n, long long &numComparisons);
    void insertSort2(int Comparable[], int n, long long &numComparisons);


    void selectionSort(int Comparable[], int n, long long &numComparisons);

private:
    static void swap(int Arr[],int bigIndex,int n);


};



#endif //SORTINGALGORITHMS_H

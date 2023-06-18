#pragma once 

void insertionSort(int array[], int size);

void merge(int array[], int leftIdx, int midIdx, int rigthIdx);

void mergeSort(int array[], int leftIdx, int rightIdx);

void swap(int array[], int x, int y);

int lomutoPartition(int array[], int leftIdx, int rightIdx);

void quickSort(int array[], int leftIdx, int rightIdx);

void partition(int array[], int leftIdx, int rightIdx, int& pPivot, int& qPivot);

void dualPivotQuickSort(int array[], int leftIdx, int rightIdx);

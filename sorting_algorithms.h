#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Bubble Sort
 *
 * Working Principle:
 * Repeatedly compares and swaps adjacent elements until the array is sorted.
 */
void bubble_sort_int(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void bubble_sort_str(char *arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j], arr[j+1]) > 0) {
                char *temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

/**
 * Selection Sort
 *
 * Working Principle:
 * Finds the smallest element and swaps it with the first unsorted element.
 */
void selection_sort_int(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int idx_min = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[idx_min]) {
                idx_min = j;
            }
        }
        if (idx_min != i) {
            int temp = arr[i];
            arr[i] = arr[idx_min];
            arr[idx_min] = temp;
        }
    }
}

void selection_sort_str(char *arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int idx_min = i;
        for (int j = i+1; j < n; j++) {
            if (strcmp(arr[j], arr[idx_min]) < 0) {
                idx_min = j;
            }
        }
        if (idx_min != i) {
            char *temp = arr[i];
            arr[i] = arr[idx_min];
            arr[idx_min] = temp;
        }
    }
}

/**
 * Insertion Sort
 *
 * Working Principle:
 * Inserts each element into the correct position in the sorted part of the array.
 */
void insertion_sort_int(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void insertion_sort_str(char *arr[], int n) {
    for (int i = 1; i < n; i++) {
        char *key = arr[i];
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/**
 * Merge Sort
 *
 * Working Principle:
 * Divides the array into halves, sorts each half, then merges them back together.
 */
void merge_int(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort_int_helper(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_int_helper(arr, left, mid);
        merge_sort_int_helper(arr, mid + 1, right);
        merge_int(arr, left, mid, right);
    }
}

void merge_sort_int(int arr[], int n) {
    merge_sort_int_helper(arr, 0, n - 1);
}

void merge_str(char *arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    char **L = (char **)malloc(n1 * sizeof(char *));
    char **R = (char **)malloc(n2 * sizeof(char *));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort_str_helper(char *arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_str_helper(arr, left, mid);
        merge_sort_str_helper(arr, mid + 1, right);
        merge_str(arr, left, mid, right);
    }
}

void merge_sort_str(char *arr[], int n) {
    merge_sort_str_helper(arr, 0, n - 1);
}

/**
 * Quick Sort
 *
 * Working Principle:
 * Selects a pivot and partitions the array so that elements less than the pivot
 * are on the left, and greater elements are on the right.
 */
int partition_int(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quick_sort_int_helper(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition_int(arr, low, high);
        quick_sort_int_helper(arr, low, pi - 1);
        quick_sort_int_helper(arr, pi + 1, high);
    }
}

void quick_sort_int(int arr[], int n) {
    quick_sort_int_helper(arr, 0, n - 1);
}

int partition_str(char *arr[], int low, int high) {
    char *pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            char *temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    char *temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quick_sort_str_helper(char *arr[], int low, int high) {
    if (low < high) {
        int pi = partition_str(arr, low, high);
        quick_sort_str_helper(arr, low, pi - 1);
        quick_sort_str_helper(arr, pi + 1, high);
    }
}

void quick_sort_str(char *arr[], int n) {
    quick_sort_str_helper(arr, 0, n - 1);
}

/**
 * Shell Sort
 *
 * Working Principle:
 * An optimization of insertion sort that uses a gap which decreases over time.
 */
void shell_sort_int(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void shell_sort_str(char *arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            char *temp = arr[i];
            int j;
            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

#endif

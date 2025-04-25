#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <psapi.h>
#include "sorting_algorithms.h"

// Measure time and estimated memory for sorting integer arrays
double measure_sort_time_int(void (*sort_func)(int[], int), int arr[], int n, size_t *estimated_memory) {
    clock_t start = clock();
    sort_func(arr, n);
    clock_t end = clock();
    *estimated_memory = n * sizeof(int);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// Measure time and estimated memory for sorting string arrays
double measure_sort_time_str(void (*sort_func)(char *[], int), char *arr[], int n, size_t *estimated_memory) {
    clock_t start = clock();
    sort_func(arr, n);
    clock_t end = clock();
    *estimated_memory = n * sizeof(char *);
    for (int i = 0; i < n; i++) *estimated_memory += strlen(arr[i]) + 1;
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// Create a copy of an integer array
int *copy_array_int(int source[], int n) {
    int *dest = malloc(n * sizeof(int));
    memcpy(dest, source, n * sizeof(int));
    return dest;
}

// Create a deep copy of a string array
char **copy_array_str(char *source[], int n) {
    char **dest = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) dest[i] = strdup(source[i]);
    return dest;
}

// Free memory for string array
void free_array_str(char **arr, int n) {
    for (int i = 0; i < n; i++) free(arr[i]);
    free(arr);
}

// Read integer data from file
int *read_data_int(const char *filename, int count, size_t *estimated_memory) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;
    int *arr = malloc(count * sizeof(int));
    *estimated_memory = count * sizeof(int);
    for (int i = 0; i < count && fscanf(file, "%d", &arr[i]) == 1; i++);
    fclose(file);
    return arr;
}

// Read string data from file
char **read_data_str(const char *filename, int count, size_t *estimated_memory) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;
    char **arr = malloc(count * sizeof(char *));
    *estimated_memory = count * sizeof(char *);
    char buffer[100];
    for (int i = 0; i < count && fgets(buffer, sizeof(buffer), file); i++) {
        buffer[strcspn(buffer, "\n")] = '\0';
        arr[i] = strdup(buffer);
        *estimated_memory += strlen(buffer) + 1;
    }
    fclose(file);
    return arr;
}

// Run sorting algorithm test and print results
void test_sort_algorithm(FILE *result_file, const char *data_type, int size, void *original_data,
                         void (*sort_funcs[])(void *, int),
                         const char *algo_names[], int is_string) {
    printf("\n+------------+------------+----------+----------------+------------------+\n");
    printf("| %-10s | %-10s | %-8s | %-14s | %-16s |\n",
           "Algorithm", "Data Type", "Size", "Time (seconds)", "Est Mem (bytes)");
    printf("+------------+------------+----------+----------------+------------------+\n");

    for (int i = 0; i < 6; i++) {
        size_t est_mem = 0;
        double time;
        if (!is_string) {
            int *copy = copy_array_int((int *)original_data, size);
            time = measure_sort_time_int((void (*)(int[], int))sort_funcs[i], copy, size, &est_mem);
            printf("| %-10s | %-10s | %-8d | %-14.6f | %-16zu |\n",
                   algo_names[i], data_type, size, time, est_mem);
            fprintf(result_file, "%s,%s,%d,%.6f,%zu\n",
                    algo_names[i], data_type, size, time, est_mem);
            free(copy);
        } else {
            char **copy = copy_array_str((char **)original_data, size);
            time = measure_sort_time_str((void (*)(char *[], int))sort_funcs[i], copy, size, &est_mem);
            printf("| %-10s | %-10s | %-8d | %-14.6f | %-16zu |\n",
                   algo_names[i], data_type, size, time, est_mem);
            fprintf(result_file, "%s,%s,%d,%.6f,%zu\n",
                    algo_names[i], data_type, size, time, est_mem);
            free_array_str(copy, size);
        }
    }
    printf("+------------+------------+----------+----------------+------------------+\n");
}

// === Main Program ===
int main() {
    int data_sizes[] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};
    int num_sizes = sizeof(data_sizes) / sizeof(data_sizes[0]);

    FILE *result_file = fopen("sorting_results.csv", "w");
    if (!result_file) {
        perror("Failed to open result file");
        return 1;
    }
    fprintf(result_file, "Algorithm,Data Type,Size,Time (seconds),Estimated Memory (bytes)\n");

    const char *algo_names[] = {"Bubble", "Selection", "Insertion", "Merge", "Quick", "Shell"};
    void (*sort_int[])(void *, int) = {
        (void (*)(void *, int))bubble_sort_int,
        (void (*)(void *, int))selection_sort_int,
        (void (*)(void *, int))insertion_sort_int,
        (void (*)(void *, int))merge_sort_int,
        (void (*)(void *, int))quick_sort_int,
        (void (*)(void *, int))shell_sort_int
    };
    void (*sort_str[])(void *, int) = {
        (void (*)(void *, int))bubble_sort_str,
        (void (*)(void *, int))selection_sort_str,
        (void (*)(void *, int))insertion_sort_str,
        (void (*)(void *, int))merge_sort_str,
        (void (*)(void *, int))quick_sort_str,
        (void (*)(void *, int))shell_sort_str
    };

    for (int i = 0; i < num_sizes; i++) {
        int size = data_sizes[i];
        printf("\n--- Testing size: %d ---\n", size);

        size_t dummy_memory;
        int *int_data = read_data_int("data_angka.txt", size, &dummy_memory);
        if (int_data) {
            test_sort_algorithm(result_file, "number", size, int_data, sort_int, algo_names, 0);
            free(int_data);
        } else {
            printf("Failed to read data_angka.txt\n");
        }

        char **str_data = read_data_str("data_kata.txt", size, &dummy_memory);
        if (str_data) {
            test_sort_algorithm(result_file, "word", size, str_data, sort_str, algo_names, 1);
            free_array_str(str_data, size);
        } else {
            printf("Failed to read data_kata.txt\n");
        }
    }

    fclose(result_file);
    printf("\nAll tests completed. Results saved to sorting_results.csv\n");
    return 0;
}

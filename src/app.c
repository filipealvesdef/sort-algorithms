/**    _                _ _                   ___             _      _
 *    / \   _ __   __ _| (_)___  ___    ___  |  _ \ _ __ ___ (_) ___| |_ ___
 *   / _ \ | '_ \ / _` | | / __|/ _ \  / _ \ | |_) | '__/ _ \| |/ _ \ __/ _ \
 *  / ___ \| | | | (_| | | \__ \  __/ |  __/ |  __/| | | (_) | |  __/ |  (_) |
 * /_/   \_\_| |_|\__,_|_|_|___/\___|  \___| |_|   |_|  \___// |\___|\__\___/
 *                                                         |__/
 *      _           _    _                  _ _
 *   __| | ___     / \  | | __ _  ___  _ __(_) |_ _ __ ___   ___  ___
 *  / _` |/ _ \   / _ \ | |/ _` |/ _ \| '__| | __| '_ ` _ \ / _ \/ __|
 * | (_| |  __/  / ___ \| | (_| | (_) | |  | | |_| | | | | | (_) \__ \
 *  \__,_|\___| /_/   \_\_|\__, |\___/|_|  |_|\__|_| |_| |_|\___/|___/
 *                         |___/
 *
 * Autor: Filipe Alves de Fernando
 * Professor: Daniel Carlos Guimarães Pedronette
 * Disiciplina: Análise e Projeto de Algoritmos
 * Programa de Pós Graduação em Ciência da Computação
 *
 */

#include <time.h>
#include <sort.h>
#include <vector.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Benchmark parameters
static const unsigned int exec_times = 30;
static const unsigned int max_input_val = 10;
static const unsigned int input_len_inc = 20;
static const unsigned int input_max_len = 2000;
static const char output_dir[] = "output";

// Left most column is reserved to store the input size
static const unsigned int cols = exec_times + 1;
static const unsigned int rows = (input_max_len / input_len_inc);

void save_benchmark(const char *output_name, double **benchmark)
{
    FILE *f = fopen(output_name, "wt");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            fprintf(f, "%lf ", benchmark[i][j]);
        fprintf(f, "\n");
    }
    fclose(f);
}

int main(int argc, char *argv[])
{
    static unsigned int current_input_size = input_len_inc;
    clock_t start;
    double elapsed;

    struct stat st = {0};

    if (stat(output_dir, &st) == -1)
        mkdir(output_dir, 0700);

    // Allocating matrix for storing results for each test
    double **selection_sort_rand = (double**) malloc(sizeof(double**) * rows);
    double **selection_sort_sorted = (double**) malloc(sizeof(double**) * rows);
    double **selection_sort_reversed = (double**) malloc(sizeof(double**) * rows);

    double **insertion_sort_rand = (double**) malloc(sizeof(double**) * rows);
    double **insertion_sort_sorted = (double**) malloc(sizeof(double**) * rows);
    double **insertion_sort_reversed = (double**) malloc(sizeof(double**) * rows);

    double **merge_sort_rand = (double**) malloc(sizeof(double**) * rows);
    double **merge_sort_sorted = (double**) malloc(sizeof(double**) * rows);
    double **merge_sort_reversed = (double**) malloc(sizeof(double**) * rows);

    double **heap_sort_rand = (double**) malloc(sizeof(double**) * rows);
    double **heap_sort_sorted = (double**) malloc(sizeof(double**) * rows);
    double **heap_sort_reversed = (double**) malloc(sizeof(double**) * rows);

    double **quick_sort_rand = (double**) malloc(sizeof(double**) * rows);
    double **quick_sort_sorted = (double**) malloc(sizeof(double**) * rows);
    double **quick_sort_reversed = (double**) malloc(sizeof(double**) * rows);

    for (int i = 0; i < rows; i++) {
        selection_sort_rand[i] = (double*) malloc(sizeof(double*) * cols);
        selection_sort_sorted[i] = (double*) malloc(sizeof(double*) * cols);
        selection_sort_reversed[i] = (double*) malloc(sizeof(double*) * cols);

        insertion_sort_rand[i] = (double*) malloc(sizeof(double*) * cols);
        insertion_sort_sorted[i] = (double*) malloc(sizeof(double*) * cols);
        insertion_sort_reversed[i] = (double*) malloc(sizeof(double*) * cols);

        merge_sort_rand[i] = (double*) malloc(sizeof(double*) * cols);
        merge_sort_sorted[i] = (double*) malloc(sizeof(double*) * cols);
        merge_sort_reversed[i] = (double*) malloc(sizeof(double*) * cols);

        heap_sort_rand[i] = (double*) malloc(sizeof(double*) * cols);
        heap_sort_sorted[i] = (double*) malloc(sizeof(double*) * cols);
        heap_sort_reversed[i] = (double*) malloc(sizeof(double*) * cols);

        quick_sort_rand[i] = (double*) malloc(sizeof(double*) * cols);
        quick_sort_sorted[i] = (double*) malloc(sizeof(double*) * cols);
        quick_sort_reversed[i] = (double*) malloc(sizeof(double*) * cols);
    }

    while (current_input_size <= input_max_len) {
        int row = current_input_size / input_len_inc - 1;
        selection_sort_rand[row][0] = current_input_size;
        selection_sort_sorted[row][0] = current_input_size;
        selection_sort_reversed[row][0] = current_input_size;

        insertion_sort_rand[row][0] = current_input_size;
        insertion_sort_sorted[row][0] = current_input_size;
        insertion_sort_reversed[row][0] = current_input_size;

        merge_sort_rand[row][0] = current_input_size;
        merge_sort_sorted[row][0] = current_input_size;
        merge_sort_reversed[row][0] = current_input_size;

        heap_sort_rand[row][0] = current_input_size;
        heap_sort_sorted[row][0] = current_input_size;
        heap_sort_reversed[row][0] = current_input_size;

        quick_sort_rand[row][0] = current_input_size;
        quick_sort_sorted[row][0] = current_input_size;
        quick_sort_reversed[row][0] = current_input_size;

        for (int exec = 1; exec <= exec_times; exec++) {
            vec_t v = create_vec(current_input_size, max_input_val);

            // Executing selection sort with a random array
            start = clock();
            selection_sort(v);
            elapsed = (double) clock() - start;
            selection_sort_rand[row][exec] = elapsed;

            // Testing correctiness
            if (!is_sorted(v))
                printf("Selection sort is not correct for %d array length\n", current_input_size);

            // Executing selection sort with a sorted array
            start = clock();
            selection_sort(v);
            elapsed = (double) clock() - start;
            selection_sort_sorted[row][exec] = elapsed;

            // Executing selection sort with a reversed array
            vec_t r = rev_vec(v);
            start = clock();
            selection_sort(r);
            elapsed = (double) clock() - start;
            selection_sort_reversed[row][exec] = elapsed;

            destroy_vec(v);
            destroy_vec(r);

            // Executing insertion sort with a random array
            v = create_vec(current_input_size, max_input_val);
            start = clock();
            insertion_sort(v);
            elapsed = (double) clock() - start;
            insertion_sort_rand[row][exec] = elapsed;

            // Testing correctiness
            if (!is_sorted(v))
                printf("Insertion sort is not correct for %d array length\n", current_input_size);

            // Executing selection sort with a sorted array
            start = clock();
            insertion_sort(v);
            elapsed = (double) clock() - start;
            insertion_sort_sorted[row][exec] = elapsed;

            // Executing selection sort with a reversed array
            r = rev_vec(v);
            start = clock();
            selection_sort(r);
            elapsed = (double) clock() - start;
            insertion_sort_reversed[row][exec] = elapsed;

            destroy_vec(v);
            destroy_vec(r);

            // Executing merge sort with a random array
            v = create_vec(current_input_size, max_input_val);
            start = clock();
            merge_sort(v);
            elapsed = (double) clock() - start;
            merge_sort_rand[row][exec] = elapsed;

            // Testing correctiness
            if (!is_sorted(v))
                printf("Merge sort is not correct for %d array length\n", current_input_size);

            // Executing merge sort with a sorted array
            start = clock();
            merge_sort(v);
            elapsed = (double) clock() - start;
            merge_sort_sorted[row][exec] = elapsed;

            // Executing merge sort with a reversed array
            r = rev_vec(v);
            start = clock();
            merge_sort(r);
            elapsed = (double) clock() - start;
            merge_sort_reversed[row][exec] = elapsed;

            destroy_vec(v);
            destroy_vec(r);

            // Executing heap sort with a random array
            v = create_vec(current_input_size, max_input_val);
            start = clock();
            heap_sort(v);
            elapsed = (double) clock() - start;
            heap_sort_rand[row][exec] = elapsed;

            // Testing correctiness
            if (!is_sorted(v))
                printf("Heap sort is not correct for %d array length\n", current_input_size);

            // Executing heap sort with a sorted array
            start = clock();
            heap_sort(v);
            elapsed = (double) clock() - start;
            heap_sort_sorted[row][exec] = elapsed;

            // Executing heap sort with a reversed array
            r = rev_vec(v);
            start = clock();
            heap_sort(r);
            elapsed = (double) clock() - start;
            heap_sort_reversed[row][exec] = elapsed;

            destroy_vec(v);
            destroy_vec(r);

            // Executing quick sort with a random array
            v = create_vec(current_input_size, max_input_val);
            start = clock();
            quicksort(v);
            elapsed = (double) clock() - start;
            quick_sort_rand[row][exec] = elapsed;

            // Testing correctiness
            if (!is_sorted(v))
                printf("Quick sort is not correct for %d array length\n", current_input_size);

            // Executing heap sort with a sorted array
            start = clock();
            quicksort(v);
            elapsed = (double) clock() - start;
            quick_sort_sorted[row][exec] = elapsed;

            // Executing heap sort with a reversed array
            r = rev_vec(v);
            start = clock();
            quicksort(r);
            elapsed = (double) clock() - start;
            quick_sort_reversed[row][exec] = elapsed;

            destroy_vec(v);
            destroy_vec(r);
        }
        current_input_size+=input_len_inc;
    }

    save_benchmark("output/selection_sort_rand.out", selection_sort_rand);
    save_benchmark("output/selection_sort_sorted.out", selection_sort_sorted);
    save_benchmark("output/selection_sort_reversed.out", selection_sort_reversed);
    save_benchmark("output/insertion_sort_rand.out", insertion_sort_rand);
    save_benchmark("output/insertion_sort_sorted.out", insertion_sort_sorted);
    save_benchmark("output/insertion_sort_reversed.out", insertion_sort_reversed);
    save_benchmark("output/merge_sort_rand.out", merge_sort_rand);
    save_benchmark("output/merge_sort_sorted.out", merge_sort_sorted);
    save_benchmark("output/merge_sort_reversed.out", merge_sort_reversed);
    save_benchmark("output/heap_sort_rand.out", heap_sort_rand);
    save_benchmark("output/heap_sort_sorted.out", heap_sort_sorted);
    save_benchmark("output/heap_sort_reversed.out", heap_sort_reversed);
    save_benchmark("output/quicksort_rand.out", quick_sort_rand);
    save_benchmark("output/quicksort_sorted.out", quick_sort_sorted);
    save_benchmark("output/quicksort_reversed.out", quick_sort_reversed);

    return 0;
}

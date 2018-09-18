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

#include <vector.h>
#include <sort.h>

void swap(vec_t v, int l, int r)
{
    int tmp = v->vals[l];
    v->vals[l] = v->vals[r];
    v->vals[r] = tmp;
}

void selection_sort(vec_t v)
{
    for (int i = 0; i < v->length - 1; i++) {
        int min = i;
        for (int j = i + 1; j < v->length; j++)
            if (v->vals[j] < v->vals[min])
                min = j;
        if (min > i)
            swap(v, i, min);
    }
}

void insertion_sort(vec_t v)
{
    for (int i = 1; i < v->length; i++) {
        int j = i - 1;
        int val = v->vals[i];
        while (j >= 0 && v->vals[j] > val) {
            v->vals[j + 1] = v->vals[j];
            j--;
        }
        v->vals[j + 1] = val;
    }
}

void merge(vec_t v, vec_t b, int p, int q, int r)
{
    int i, j;
    for (i = p; i <= q; i++) {
        b->vals[i] = v->vals[i];
    }
    for (j = q + 1; j <= r; j++)
        b->vals[r + q + 1 - j] = v->vals[j];
    i = p;
    j = r;
    for (int k = p; k <= r; k++) {
        if (b->vals[i] <= b->vals[j]) {
            v->vals[k] = b->vals[i];
            i++;
        } else {
            v->vals[k] = b->vals[j];
            j--;
        }
    }
}

void _merge_sort(vec_t v, vec_t aux, int p, int r)
{
    if (p < r) {
        int q = (p + r) / 2;
        _merge_sort(v, aux, p, q);
        _merge_sort(v, aux, q + 1, r);
        merge(v, aux, p, q, r);
    }
}

void merge_sort(vec_t v)
{
    vec_t aux = create_vec(v->length, 1);
    _merge_sort(v, aux, 0, v->length - 1);
    destroy_vec(aux);
}

void max_heapfy(vec_t v, int length, int i)
{
    int l = i * 2 + 1;
    int r = i * 2 + 2;
    int max = i;
    if (l < length && v->vals[l] > v->vals[max])
        max = l;
    if (r < length && v->vals[r] > v->vals[max])
        max = r;
    if (max > i) {
        swap(v, i, max);
        max_heapfy(v, length, max);
    }
}

void build_max_heap(vec_t v)
{
    int length = v->length;
    for (int i = length / 2; i >= 0; i--)
        max_heapfy(v, length, i);
}

void heap_sort(vec_t v)
{
    build_max_heap(v);
    for (int i = v->length - 1, m = v->length - 1; i > 0; i--, m--) {
        swap(v, 0, i);
        max_heapfy(v, m, 0);
    }
}

static int partition(vec_t v, int p, int r)
{
    int x = v->vals[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (v->vals[j] <= x) {
            i++;
            swap(v, i, j);
        }
    }
    swap(v, i + 1, r);
    return i + 1;
}

void _quicksort(vec_t v, int p, int r)
{
    if (p < r) {
        int q = partition(v, p, r);
        _quicksort(v, p, q - 1);
        _quicksort(v, q + 1, r);
    }
}

void quicksort(vec_t v)
{
    _quicksort(v, 0, v->length - 1);
}

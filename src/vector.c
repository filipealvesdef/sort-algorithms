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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector.h>

vec_t create_vec(int length, int max_rand)
{
    vec_t v = (vec_t) malloc(sizeof(vec_t));
    v->length = length;
    srand(time(NULL));
    v->vals = (int*) malloc(sizeof(int) * v->length);
    for (int i = 0; i < v->length; i++)
        v->vals[i] = rand() % max_rand;
    return v;
}

vec_t rev_vec(vec_t v)
{
    vec_t r = (vec_t) malloc(sizeof(vec_t));
    r->length = v->length;
    r->vals = (int*) malloc(sizeof(int) * r->length);
    for (int i = v->length; i > 0; i--)
        r->vals[r->length - i] = v->vals[i - 1];
    return r;
}

int is_sorted(vec_t v)
{
    for (int i = 1; i < v->length; i++)
        if (v->vals[i] < v->vals[i - 1])
            return 0;
    return 1;
}

void destroy_vec(vec_t v)
{
    free(v->vals);
    free(v);
}

void print_vec(vec_t v)
{
    printf("[");
    for (int i = 0; i < v->length; i++) {
        printf("%d", v->vals[i]);
        i + 1 < v->length ? printf(", ") : printf("]\n");
    }
}

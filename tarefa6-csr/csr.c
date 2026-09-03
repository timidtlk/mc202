#include <stdio.h>
#include <stdlib.h>

typedef struct _vc {
    int i;
    int j;
    int x;
} vc;

typedef struct _csr {
    int* A;
    int* C;
    int* R;
} csr;

int comparar(const void* a, const void* b) {
    vc valA = *(const vc *)a;
    vc valB = *(const vc *)b;

    if (valA.i < valB.i) return -1;
    if (valA.i > valB.i) return 1;
    if (valA.j < valB.j) return -1;
    if (valA.j > valB.j) return 1;
    return 0;
}

csr* to_csr(int k, vc v[]) {
    csr* new = (csr*) malloc(sizeof(csr));

    new->A = calloc(k, sizeof(int));
    new->C = calloc(k, sizeof(int));
    new->R = calloc(v[k-1].i + 1, sizeof(int));

    int soma = 0;
    for (int i = 0; i < k; i++) {
        *(new->A+i) = v[i].x;
        *(new->C+i) = v[i].j;
        for (int j = 0; j < k; j++) {
            if (v[j].i >= i) {
                soma += j+1;
                *(new->R+i) = soma;
            }
        }
    }

    return new;
}

int get_ij(csr* m, int i, int j) {
    int qtd = m->R[i+1] - m->R[i];
    if (!qtd) return 0;
    
    for (int k = m->R[i]; k < m->R[i+1]-1; k++) {
        if (m->C[k] == j) return m->A[k];
    }
    return 0;
}

int main(void) {
    int size;
    scanf("%d", &size);

    vc v[size];
    for (int i = 0; i < size; i++) {
        vc tmp;
        scanf("%d %d %d", &tmp.i, &tmp.j, &tmp.x);
        v[i] = tmp;
    }
    
    qsort(v, size, sizeof(vc), comparar);

    csr* data = to_csr(size, v);
    
    int i, j;
    do {
        scanf("%d %d", &i, &j);

        if (i != -1 && j != -1) {
            printf("(%d,%d) = %d\n", i, j, get_ij(data, i, j));
        }
    } while (i != -1 && j != -1);

    free(data->A);
    free(data->C);
    free(data->R);
    free(data);

    return 0;
}